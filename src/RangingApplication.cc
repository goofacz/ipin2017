#include <cassert>

#include <inet/common/INETDefs.h>
#include <Ieee802Ctrl.h>
#include <IRadio.h>

#include "RangingApplication.h"

using namespace omnetpp;
using namespace inet;
using namespace std;

namespace ipin2017
{

Define_Module(RangingApplication);

void
RangingApplication::initialize (int stage)
{
    cSimpleModule::initialize(stage);

    if (stage == INITSTAGE_APPLICATION_LAYER)
    {
        const auto ranging_host = getParentModule ();
        assert (ranging_host);
        const auto mac = ranging_host->getModuleByPath (".nic.mac");
        assert (mac);

        const auto& address = mac->par("address");
        assert (address.getType () == cPar::STRING);
        localAddress.setAddress (address.stringValue ());

        const auto radio = ranging_host->getModuleByPath(".nic.radio");
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
    }
}

const MACAddress&
RangingApplication::getLocalAddress () const
{
    return localAddress;
}

void
RangingApplication::sendMacPacket (const inet::MACAddress& destinationAddress,
                                   unique_ptr<RangingPacket> packet,
                                   unsigned int delay,
                                   SimTimeUnit delay_unit)
{
    assert (packet);

    auto controlInformation = unique_ptr<Ieee802Ctrl> {new Ieee802Ctrl};
    controlInformation->setSourceAddress (getLocalAddress ());
    controlInformation->setDest (destinationAddress);
    packet->setControlInfo (controlInformation.release ());
    sendDelayed (packet.release (), SimTime {delay, delay_unit}, "out");
}

void
RangingApplication::scheduleSelfMessage (unique_ptr<cMessage> message,
                                         unsigned int delay,
                                         SimTimeUnit delay_unit)
{
    const auto timestamp = simTime () + SimTime {delay, delay_unit};
    scheduleAt (timestamp, message.release ());
}

const RangingApplication::RecentTransmitterTimestamps&
RangingApplication::getRecentTransmitterTimestamps () const
{
    return recentTransmitterTimestamps;
}

const RangingApplication::RecentReceiverTimestamps&
RangingApplication::getRRecentReceiverTimestamps () const
{
    return recentReceiverTimestamps;
}

int
RangingApplication::numInitStages () const
{
    return NUM_INIT_STAGES;
}

void
RangingApplication::transmissionStateChangedCallback (cComponent* source,
                                                      simsignal_t signalID,
                                                      long value,
                                                      cObject* details)
{
    const auto state = static_cast<physicallayer::IRadio::TransmissionState> (value);
    switch (state)
    {
        case physicallayer::IRadio::TRANSMISSION_STATE_UNDEFINED:
            recentTransmitterTimestamps.undefined = simTime ();
            break;
        case physicallayer::IRadio::TRANSMISSION_STATE_IDLE:
            recentTransmitterTimestamps.idle = simTime ();
            break;
        case physicallayer::IRadio::TRANSMISSION_STATE_TRANSMITTING:
            recentTransmitterTimestamps.transmitting = simTime ();
            break;
        default:
            throw runtime_error ("Unknown nic.transmissionStateChanged state!");
    }
}

void
RangingApplication::receptionStateChangedCallback (cComponent* source,
                                                   simsignal_t signalID,
                                                   long value,
                                                   cObject* details)
{
    const auto state = static_cast<physicallayer::IRadio::ReceptionState> (value);
    switch (state)
    {
        case physicallayer::IRadio::RECEPTION_STATE_UNDEFINED:
            recentReceiverTimestamps.undefined = simTime ();
            break;
        case physicallayer::IRadio::RECEPTION_STATE_IDLE:
            recentReceiverTimestamps.idle = simTime ();
            break;
        case physicallayer::IRadio::RECEPTION_STATE_BUSY:
            recentReceiverTimestamps.busy = simTime ();
            break;
        case physicallayer::IRadio::RECEPTION_STATE_RECEIVING:
            recentReceiverTimestamps.receiving = simTime ();
            break;
        default:
            throw runtime_error ("Unknown nic.receptionStateChangedCallback state!");
    }
}

} //namespace ipin2017
