#pragma once

#include <omnetpp.h>

#include "RangingApplication.h"

namespace ipin2017
{

class AnchorRangingApplication :
    public RangingApplication
{
  private:
    void initialize(int stage) override;
};

}; // namespace ipin2017
