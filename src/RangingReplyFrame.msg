cplusplus {{
#include <Coord.h>
#include <omnetpp.h>
#include "Frame_m.h"
}}

packet ipin2017::Frame;
struct inet::Coord;
struct omnetpp::SimTime;

namespace ipin2017;

packet RangingReplyFrame extends ipin2017::Frame
{
    type = ipin2017::RANGING_REPLY_FRAME;
    name = "RangingReplyFrame";

    inet::Coord realPosition;
    omnetpp::SimTime processingDelay;
}