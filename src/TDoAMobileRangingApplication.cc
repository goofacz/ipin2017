#include <cassert>
#include <ctime>
#include <iostream>
#include <fstream>

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

    if (stage == INITSTAGE_APPLICATION_LAYER)
    {
        const auto rangingHost = check_and_cast<RangingHost*> (getParentModule ());
        rangingHost->addRxStateChangedCallback ([this] (IRadio::ReceptionState state) { this->onRxStateChangedCallback (state); });
    }
}

void
TDoAMobileRangingApplication::finish ()
{
    RangingApplication::finish ();
    storeResults ();
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

void
TDoAMobileRangingApplication::storeResults ()
{
    auto currentTimestamp = time (nullptr);
    auto currentTime = localtime (&currentTimestamp);
    ostringstream fileName;
    fileName << "tdoa_simulation_result_" <<
             setw (2) << setfill ('0') <<  currentTime->tm_hour << "_" << setw (2) << setfill ('0') << currentTime->tm_min << "_" << setw (2) << setfill ('0') << currentTime->tm_sec << "__" <<
             setw (2) << setfill ('0') << currentTime->tm_mday << "_" << setw (2) << setfill ('0') << currentTime->tm_mon << "_" << currentTime->tm_year + 1900;

    ofstream resultFile;
    resultFile.open (fileName.str (), ios_base::out | ios_base::app);

    for (const auto& entry : receivedBeacons)
    {
        const auto packetControlInformation = check_and_cast<const Ieee802Ctrl*> (entry.beacon->getControlInfo ());
        const auto sourceAddress = packetControlInformation->getSourceAddress ();

        resultFile << entry.beacon->getSequenceNumber () << ',';
        resultFile << sourceAddress.getInt () << ',';
        resultFile << entry.receptionTimestamp.inUnit (SIMTIME_PS) << ',';
        resultFile << entry.beacon->getPosition ().x << ',';
        resultFile << entry.beacon->getPosition ().y << ',';
        resultFile << entry.realPosition.x << ',';
        resultFile << entry.realPosition.y << '\n';
    }

    resultFile.flush ();
}

}; // namespace ipin2017
