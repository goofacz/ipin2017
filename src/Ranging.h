#pragma once

#include <vector>

#include <omnetpp.h>
#include <MACAddress.h>
#include <Coord.h>

namespace ipin2017
{

struct MobileReplyEcho
{
    omnetpp::SimTime receptionTimestamp;
    inet::Coord helperAnchorPosition;
    inet::MACAddress helperAnchorAddress;
};

struct MobileReply
{
    omnetpp::SimTime receptionTimestamp;
    inet::Coord mobileRealPosition;
    inet::MACAddress mobileAddress;

    std::vector<MobileReplyEcho> echos;
};

struct BeaconEcho
{
    omnetpp::SimTime receptionTimestamp;
    inet::Coord helperAnchorPosition;
    inet::MACAddress helperAnchorAddress;
};

struct Beacon
{
    unsigned int sequenceNumber;
    omnetpp::SimTime transmissionTimestamp;
    inet::Coord masterAnchorPosition;
    inet::MACAddress masterAnchorAddress;

    std::vector<BeaconEcho> beaconEchos;
    std::vector<MobileReply> mobileReplies;
};

} // namespace ipin2017
