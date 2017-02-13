#include <cassert>

#include <inet/common/INETDefs.h>
#include <Ieee802Ctrl.h>

#include "RangingApplication.h"

using namespace omnetpp;
using namespace inet;

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
        const auto address = mac->par("address");

        assert (address);
        assert (address.getType () == cPar::STRING);
        localAddress.setAddress (address.stringValue ());
    }
}

const MACAddress&
RangingApplication::getLocalAddress () const
{
    return localAddress;
}

int
RangingApplication::numInitStages() const
{
    return NUM_INIT_STAGES;
}

} //namespace ipin2017
