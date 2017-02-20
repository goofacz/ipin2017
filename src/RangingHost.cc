#include <cassert>

#include <inet/common/INETDefs.h>
#include <Radio.h>

#include "RangingHost.h"

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

const SimTime&
RangingHost::getTxBeginTimestamp () const
{
    return txBeginTimestamp;
}

const SimTime&
RangingHost::getRxBeginTimestamp () const
{
    return rxBeginTimestamp;
}

const Coord&
RangingHost::getCurrentPosition () const
{
    return currentPosition;
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
        assert (radio);

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

        rxCurrentState = radio->getReceptionState ();
        txCurrentState = radio->getTransmissionState ();

        // Setup mobility
        const auto mobility = getModuleByPath(".mobility");
        assert (mobility);

        auto mobilityStateChangedListenerFunction = [this] (cComponent* source, simsignal_t signalID, cObject* value, cObject* details)  {
            this->mobilityStateChangedCallback (source, signalID, value, details);
        };
        mobilityStateChangedListener = mobilityStateChangedListenerFunction;
        mobility->subscribe("mobilityStateChanged", &mobilityStateChangedListener);
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
    assert (txCurrentState != IRadio::TRANSMISSION_STATE_UNDEFINED);

    const auto nextState = static_cast<IRadio::TransmissionState> (value);
    if (txCurrentState == IRadio::TRANSMISSION_STATE_IDLE && nextState == IRadio::TRANSMISSION_STATE_TRANSMITTING)   {
        txBeginTimestamp = simTime ();
    }

    txCurrentState = nextState;
}

void
RangingHost::receptionStateChangedCallback (cComponent* source,
                                            simsignal_t signalID,
                                            long value,
                                            cObject* details)
{
    assert (rxCurrentState != IRadio::RECEPTION_STATE_UNDEFINED);

    const auto nextState = static_cast<IRadio::ReceptionState> (value);
    if (rxCurrentState == IRadio::RECEPTION_STATE_IDLE && nextState == IRadio::RECEPTION_STATE_RECEIVING)   {
        rxBeginTimestamp = simTime ();
    }

    rxCurrentState = nextState;
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
