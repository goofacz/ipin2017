cplusplus {{
#include <Coord.h>
#include "Frame_m.h"
}}

packet ipin2017::Frame;
struct inet::Coord;

namespace ipin2017;

packet RangingReplyFrame extends ipin2017::Frame
{
    type = ipin2017::RANGING_REPLY_FRAME;
    name = "RangingReplyFrame";

    inet::Coord realPosition;
}