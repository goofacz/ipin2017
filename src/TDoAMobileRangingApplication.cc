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
TDoAMobileRangingApplication::initialize (int stage)
{
    RangingApplication::initialize (stage);
}

void
TDoAMobileRangingApplication::finish ()
{
    RangingApplication::finish ();
    // TODO
}

void
TDoAMobileRangingApplication::handleMessage (cMessage* message)
{
    const auto rangingHost = check_and_cast<RangingHost*> (getParentModule ());
    unique_ptr<const BeaconFrame> frame {check_and_cast<BeaconFrame*> (message)};
    receivedBeacons.emplace_back (move (frame), beaconReceptionTimestamp, rangingHost->getCurrentPosition ());
}

void
TDoAMobileRangingApplication::onRxStateChangedCallback (IRadio::ReceptionState state)
{
    if (state == IRadio::RECEPTION_STATE_RECEIVING)    {
        beaconReceptionTimestamp = simTime ();
    }
}

TDoAMobileRangingApplication::ReceivedBeacon::ReceivedBeacon (unique_ptr<const BeaconFrame> beacon,
                                                              SimTime receptionTimestamp,
                                                              Coord realPosition) :
    beacon {move (beacon)},
    receptionTimestamp {move (receptionTimestamp)},
    realPosition {move (realPosition)}

{
    // ...
}

}; // namespace ipin2017
