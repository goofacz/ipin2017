#pragma once

#include <vector>
#include <omnetpp.h>

namespace ipin2017
{

class HardwareClockTest :
    public omnetpp::cSimpleModule
{
  private:
    using Timestamps = std::vector<omnetpp::SimTime>;

    void initialize() override;
    void handleMessage(omnetpp::cMessage *msg) override;
    void finish() override;
    std::vector<Timestamps> timestamps;
};

} // ipin2017
