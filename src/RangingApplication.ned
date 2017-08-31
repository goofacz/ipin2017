package ipin2017;

//
// Common base component for all ranging application components run on wirelss nodes.
//
simple RangingApplication like IRangingApplication
{
    parameters:
	    @class(RangingApplication);

	gates:
	    input in;
	    output out;
}
