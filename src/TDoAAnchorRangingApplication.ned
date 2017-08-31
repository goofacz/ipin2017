package ipin2017;

//
// Application implementing anchor side of proposed localization method.
//
simple TDoAAnchorRangingApplication extends RangingApplication
{
	parameters:
	    @class(TDoAAnchorRangingApplication);
	    // delay after which anchor will send initial message, should be set only on master anchor
	    int broadcastBeaconDelay @unit(ps) = default(0s);
	    
	    // processing time after which application should send their message after receiving message from preceding anchor
	    int echoBeaconDelay @unit(ps) = default(35ms);
	    
	    // address of preceding anchor 
	    string echoAnchorAddress = default("");
}