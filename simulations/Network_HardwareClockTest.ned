package ipin2017.simulations;

import ipin2017.HardwareClockTest;

network HardwareClockTestNetwork
{
    submodules:
        hardwareClockTest: HardwareClockTest {
            @display("p=155,107");
        }
}
