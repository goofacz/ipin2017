#pragma once

#include <omnetpp.h>

#include "RangingApplication.h"
#include "RangingReplyFrame_m.h"
#include "BeaconFrame_m.h"

namespace ipin2017
{

class HelperAnchorRangingApplication :
    public RangingApplication
{
  private:
    void initialize (int stage) override;

    void handleMessage (omnetpp::cMessage* message) override;

    void handleFrame (Frame* frame);
};

}; // namespace ipin2017
