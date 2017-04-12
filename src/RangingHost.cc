#include <cassert>

#include <inet/common/INETDefs.h>
#include <Radio.h>

#include "RangingHost.h"
#include "HardwareClock.h"

using namespace omnetpp;
using namespace inet;
using namespace inet::physicallayer;
using namespace std;

namespace ipin2017
{

Define_Module(RangingHost);

const MACAddress&
RangingHost::getLocalAddress () const
{
    return localAddress;
}

const Coord&
RangingHost::getCurrentPosition () const
{
    return currentPosition;
}

void
RangingHost::addTxStateChangedCallback (TxStateChangedCallback callback)
{
    txStateChangedcallbacks.emplace_back (move (callback));
}

void
RangingHost::addRxStateChangedCallback (RxStateChangedCallback callback)
{
    rxStateChangedcallbacks.emplace_back (move (callback));
}

void
RangingHost::initialize (int stage)
{
    cModule::initialize(stage);

    if (stage == INITSTAGE_LINK_LAYER_2)
    {
        // Get MAC address
        const auto mac = getModuleByPath (".nic.mac");
        assert (mac);

        const auto& address = mac->par("address");
        assert (address.getType () == cPar::STRING);
        localAddress.setAddress (address.stringValue ());

        // Setup radio
        const auto radio = check_and_cast<Radio*> (getModuleByPath(".nic.radio"));

        auto transmissionStateChangedFunction = [this] (cComponent* source, simsignal_t signalID, long value, cObject* details)  {
            this->transmissionStateChangedCallback (source, signalID, value, details);
        };
        transmissionStateChangedListener = transmissionStateChangedFunction;
        radio->subscribe("transmissionStateChanged", &transmissionStateChangedListener);

        auto receptionStateChangedListenerFunction = [this] (cComponent* source, simsignal_t signalID, long value, cObject* details)  {
            this->receptionStateChangedCallback (source, signalID, value, details);
        };
        receptionStateChangedListener = receptionStateChangedListenerFunction;
        radio->subscribe("receptionStateChanged", &receptionStateChangedListener);

        // Setup mobility
        auto mobility = getModuleByPath(".mobility");

        auto mobilityStateChangedListenerFunction = [this] (cComponent* source, simsignal_t signalID, cObject* value, cObject* details)  {
            this->mobilityStateChangedCallback (source, signalID, value, details);
        };
        mobilityStateChangedListener = mobilityStateChangedListenerFunction;
        mobility->subscribe("mobilityStateChanged", &mobilityStateChangedListener);

        auto iMobility = check_and_cast<IMobility*> (mobility);
        currentPosition = iMobility->getCurrentPosition ();

        auto clock = check_and_cast<HardwareClock*> (getModuleByPath(".clock"));
        setHardwareClock(clock);
    }
}

int
RangingHost::numInitStages () const
{
    return INITSTAGE_LINK_LAYER_2 + 1;
}

void
RangingHost::transmissionStateChangedCallback (cComponent* source,
                                               simsignal_t signalID,
                                               long value,
                                               cObject* details)
{
    const auto state = static_cast<IRadio::TransmissionState> (value);
    for (const auto& callback : txStateChangedcallbacks)
    {
        assert (callback);
        callback (state);
    }
}

void
RangingHost::receptionStateChangedCallback (cComponent* source,
                                            simsignal_t signalID,
                                            long value,
                                            cObject* details)
{
    const auto state = static_cast<IRadio::ReceptionState> (value);
    for (const auto& callback : rxStateChangedcallbacks)
    {
        assert (callback);
        callback (state);
    }
}

void
RangingHost::mobilityStateChangedCallback (cComponent* source,
                                           simsignal_t signalID,
                                           cObject* value,
                                           cObject* details)
{
    IMobility* mobility {check_and_cast<IMobility*> (value)};
    currentPosition = mobility->getCurrentPosition ();
}

} // namespace ipin2017
