cplusplus {{
#include <omnetpp.h>
#include <MACAddress.h>
#include <Coord.h>
#include "Frame_m.h"

using FramePointer = ipin2017::Frame*;
}}

struct omnetpp::SimTime;
struct inet::MACAddress;
struct inet::Coord;
class noncobject FramePointer;

namespace ipin2017;

message BackhaulMessage
{
    @customize(true);
	omnetpp::SimTime receptionTimestamp;
	inet::MACAddress address;
    inet::Coord position;
    FramePointer frame = nullptr;

	name = "BackhaulMessage";
}