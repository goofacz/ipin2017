package ipin2017;

simple TDoAAnchorRangingApplication extends RangingApplication
{
	parameters:
	    @class(TDoAAnchorRangingApplication);
	    int broadcastBeaconDelay @unit(ps) = default(0s);
	    int echoBeaconDelay @unit(ps) = default(35ms);
	    string echoAnchorAddress = default("");
}