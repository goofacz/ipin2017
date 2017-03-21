namespace ipin2017;

enum TDoAAnchorSelfMessageEventType
{
    BROADCAST_BEACON = 0;
}

message TDoAAnchorSelfMessage 
{
    int eventType @enum(TDoAAnchorSelfMessageEventType);
}
