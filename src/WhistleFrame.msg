cplusplus {{
#include "Frame_m.h"
}}

packet ipin2017::Frame;

namespace ipin2017;

packet WhistleFrame extends ipin2017::Frame
{
    type = ipin2017::WHISTLE_FRAME;
    name = "WhistleFrame";
    bool echoFrame = false;
}
