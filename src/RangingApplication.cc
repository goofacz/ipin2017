#include <cassert>

#include <inet/common/INETDefs.h>
#include <Ieee802Ctrl.h>

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
        const auto nic = ranging_host->getSubmodule ("nic");
        assert (nic);
        const auto mac = nic->getSubmodule ("mac");
        assert (mac);

        const auto& address = mac->par("address");
        assert (address.getType () == cPar::STRING);
        localAddress.setAddress (address.stringValue ());
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

int
RangingApplication::numInitStages () const
{
    return NUM_INIT_STAGES;
}

} //namespace ipin2017
