package ipin2017;

simple TDoAAnchorRangingApplication extends RangingApplication
{
	parameters:
	    @class(TDoAAnchorRangingApplication);
	    int broadcastBeaconDelay @unit(ms) = default(5s);
	    string simulationResultSuffix @prompt("Matlab output:") = default("_result");
}