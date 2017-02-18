package ipin2017;

simple HelperAnchorRangingApplication extends RangingApplication
{
	parameters:
	    @class(HelperAnchorRangingApplication);
	    int backhaulOutSize = default(0);

	gates:
        output backhaulOut[backhaulOutSize] @loose;
}