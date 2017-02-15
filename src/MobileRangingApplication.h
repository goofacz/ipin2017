#pragma once

#include <omnetpp.h>

#include "RangingApplication.h"

namespace ipin2017
{

class MobileRangingApplication :
    public RangingApplication
{
  private:
    void initialize(int stage) override;

    void handleMessage (omnetpp::cMessage* message) override;
};

}; // namespace ipin2017
