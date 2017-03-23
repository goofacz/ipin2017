#include <cassert>

#include <INETDefs.h>
#include <Ieee802Ctrl.h>
#include <IdealMacFrame_m.h>

#include "TDoAMobileRangingApplication.h"
#include "RangingHost.h"
#include "Utilities.h"

using namespace inet;
using namespace inet::physicallayer;
using namespace omnetpp;
using namespace std;

namespace ipin2017
{

Define_Module(TDoAMobileRangingApplication);

void
TDoAMobileRangingApplication::initialize(int stage)
{
    RangingApplication::initialize(stage);

    if (stage == INITSTAGE_APPLICATION_LAYER)
    {
        // TODO
    }
}

void
TDoAMobileRangingApplication::handleMessage (cMessage* message)
{
    const auto frame = check_and_cast<BeaconFrame*> (message);
    beaconPairs.emplace_back (frame, beaconReceptionTimestamp);
}

void
TDoAMobileRangingApplication::onRxStateChangedCallback (IRadio::ReceptionState state)
{
    if (state == IRadio::RECEPTION_STATE_RECEIVING)    {
        beaconReceptionTimestamp = simTime ();
    }
}

}; // namespace ipin2017
