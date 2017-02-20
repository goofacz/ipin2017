cplusplus {{
#include <omnetpp.h>
#include <MACAddress.h>
}}

struct omnetpp::SimTime;
struct inet::MACAddress;

namespace ipin2017;

message BackhaulMessage
{
	omnetpp::SimTime receptionTimestamp;
	inet::MACAddress sourceAddress;
	unsigned int sequenceNumber;
	
	name = "BackhaulMessage";
}