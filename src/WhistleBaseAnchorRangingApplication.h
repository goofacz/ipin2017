#pragma once

#include <omnetpp.h>
#include <IRadio.h>

#include "RangingApplication.h"
#include "BeaconFrame_m.h"

namespace ipin2017
{

class WhistleBaseAnchorRangingApplication :
    public RangingApplication
{
  private:
    void initialize (int stage) override;

    void finish () override;

    void handleMessage (omnetpp::cMessage* message) override;
};

}; // namespace ipin2017
