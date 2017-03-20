#pragma once

#include <fstream>
#include <omnetpp.h>
#include <IRadio.h>

#include "RangingApplication.h"
#include "MasterAnchorSelfMessage_m.h"
#include "RangingReplyFrame_m.h"
#include "BeaconFrame_m.h"
#include "BackhaulMessage.h"
#include "Ranging.h"

namespace ipin2017
{

class TDoAAnchorRangingApplication :
    public RangingApplication
{
  private:
    void initialize(int stage) override;

    void finish() override;

    void handleMessage (omnetpp::cMessage* message) override;
};

}; // namespace ipin2017
