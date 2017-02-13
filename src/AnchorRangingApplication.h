#pragma once

#include <omnetpp.h>

namespace ipin2017
{

class AnchorRangingApplication :
    public omnetpp::cSimpleModule
{
  private:
    void initialize(int stage) override;
    void handleMessage(cMessage *msg) override;
    int numInitStages() const override;
};

}; // namespace ipin2017
