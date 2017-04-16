package ipin2017;

module HardwareClockTest
{
    @class(HardwareClockTest);

    submodules:
        clock_c: ConstantDrift;
        clock_bd: BoundedDrift;
        clock_bdv: BoundedDriftVariation;
}
