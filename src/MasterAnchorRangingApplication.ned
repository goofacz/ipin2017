package ipin2017;

simple MasterAnchorRangingApplication extends RangingApplication
{
	parameters:
	    @class(MasterAnchorRangingApplication);
	    int broadcastBeaconDelay @unit(ms) = default(5s);
	    int backhaulInSize = default(0);

	gates:
        input backhaulIn[backhaulInSize] @loose;
}