package ipin2017;

simple MasterAnchorRangingApplication extends RangingApplication
{
	parameters:
	    @class(MasterAnchorRangingApplication);
	    int broadcastBeaconDelay @unit(ms) = default(1000ms);
	    int backhaulInSize = default(0);

	gates:
        input backhaulIn[backhaulInSize] @loose;
}