package ipin2017;

simple RangingApplication like IRangingApplication
{
    parameters:
	    @class(RangingApplication);
	    int backhaulInSize = default(0);
	    int backhaulOutSize = default(0);

    gates:
	    input in;
	    output out;

	    // Anchor-only
        input backhaulIn[backhaulInSize] @loose;
        output backhaulOut[backhaulOutSize] @loose;
}
