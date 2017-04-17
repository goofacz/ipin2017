namespace ipin2017;

enum FrameType
{
    BEACON_FRAME = 1;
    RANGING_REPLY_FRAME = 2;
    WHISTLE_FRAME = 3;
}

packet Frame 
{
    unsigned int type @enum(FrameType) = 0;
    unsigned int sequenceNumber = 0;
    
    name = "Frame";
}
