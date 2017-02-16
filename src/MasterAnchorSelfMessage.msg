namespace ipin2017;

enum MasterAnchorSelfMessageEventType
{
    BROADCAST_BEACON = 0;
}

message MasterAnchorSelfMessage 
{
    int eventType @enum(MasterAnchorSelfMessageEventType);
}
