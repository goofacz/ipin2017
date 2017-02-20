cplusplus {{
#include "Frame_m.h"
}}

packet ipin2017::Frame;

namespace ipin2017;

packet BeaconFrame extends ipin2017::Frame
{
    type = ipin2017::BEACON_FRAME;
    name = "BeaconFrame";
}
