#include <iostream>
#include <fstream>

#include <inet/common/INETDefs.h>

#include "HardwareClockTest.h"
#include "HardwareClock.h"

using namespace inet;
using namespace omnetpp;
using namespace std;

namespace ipin2017
{

Define_Module(HardwareClockTest);

void HardwareClockTest::initialize()
{
    auto message = new cMessage("clock tick");
    const auto delay = simTime() + SimTime(1, SIMTIME_MS);
    scheduleAt(delay, message);
}

void HardwareClockTest::handleMessage(cMessage *msg)
{
    const auto delay = simTime() + SimTime(1, SIMTIME_MS);
    scheduleAt(delay, msg);

    auto clock_c = check_and_cast<HardwareClock*> (getModuleByPath(".clock_c"));
    auto clock_bd = check_and_cast<HardwareClock*> (getModuleByPath(".clock_bd"));
    auto clock_bdv = check_and_cast<HardwareClock*> (getModuleByPath(".clock_bdv"));
    vector<SimTime> round;

    round.push_back(simTime());
    round.push_back(clock_c->getHWtime ());
    round.push_back(clock_bd->getHWtime ());
    round.push_back(clock_bdv->getHWtime ());

    timestamps.emplace_back (move (round));
}

void HardwareClockTest::finish ()
{
    ofstream resultFile;
    resultFile.open ("clock_test_results", ios_base::out | ios_base::app);

    for (const auto& round : timestamps)
    {
        for (const auto& timestamp : round)
        {
            resultFile << timestamp << ';';
        }

        resultFile << '\n';
    }

    resultFile.flush ();
}

} // ipin2017
