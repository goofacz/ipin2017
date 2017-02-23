#pragma once

#include <vector>

#include <omnetpp.h>
#include <MACAddress.h>
#include <Coord.h>

namespace ipin2017
{

struct MobileReplyEcho
{
    omnetpp::SimTime receptionTimestamp {0};
    inet::Coord helperAnchorPosition {0, 0};
    inet::MACAddress helperAnchorAddress {inet::MACAddress::UNSPECIFIED_ADDRESS};
};

struct MobileReply
{
    omnetpp::SimTime receptionTimestamp {0};
    inet::Coord mobileRealPosition {0, 0};
    inet::MACAddress mobileAddress {inet::MACAddress::UNSPECIFIED_ADDRESS};

    std::vector<MobileReplyEcho> echos;
};

struct BeaconEcho
{
    omnetpp::SimTime receptionTimestamp {0};
    inet::Coord helperAnchorPosition {0, 0};
    inet::MACAddress helperAnchorAddress {inet::MACAddress::UNSPECIFIED_ADDRESS};
};

struct Beacon
{
    unsigned int sequenceNumber {0};
    omnetpp::SimTime transmissionTimestamp {0};
    inet::Coord masterAnchorPosition {0, 0};
    inet::MACAddress masterAnchorAddress {inet::MACAddress::UNSPECIFIED_ADDRESS};

    std::vector<BeaconEcho> beaconEchos;
    std::vector<MobileReply> mobileReplies;
};

} // namespace ipin2017
