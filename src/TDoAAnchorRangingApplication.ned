package ipin2017;

simple TDoAAnchorRangingApplication extends RangingApplication
{
	parameters:
	    @class(TDoAAnchorRangingApplication);
	    int broadcastBeaconDelay @unit(ms) = default(0s);
	    int echoBeaconDelay @unit(us) = default(1ms);
	    string echoAnchorAddress = default("");
}