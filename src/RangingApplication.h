#pragma once

#include <omnetpp.h>

namespace ipin2017 {


class RangingApplication :
    public omnetpp::cSimpleModule
{
  protected:
    void initialize (int stage) override;
};

} //namespace ipin2017
