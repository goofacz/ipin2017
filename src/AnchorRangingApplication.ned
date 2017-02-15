package ipin2017;

simple AnchorRangingApplication extends RangingApplication
{
	parameters:
	    @class(AnchorRangingApplication);
	    bool broadcastBeacon = default(false);
	    int broadcastBeaconDelay @unit(ms) = default(1000ms);
}
