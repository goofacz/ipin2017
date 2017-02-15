namespace ipin2017;

enum AnchorSelfMessageEventType
{
    BROADCAST_BEACON = 0;
}

message AnchorSelfMessage 
{
    int eventType @enum(AnchorSelfMessageEventType);
}
