package ipin2017.simulations;

import ipin2017.RangingHost;
import inet.networklayer.configurator.generic.GenericNetworkConfigurator;
import inet.physicallayer.idealradio.IdealRadioMedium;
import inet.visualizer.integrated.IntegratedCanvasVisualizer;

network MovingNetwork
{
    parameters:
        @display("bgb=700,700");

    submodules:
        visualizer: IntegratedCanvasVisualizer {
            @display("p=44.46,79.8");
        }

        configurator: GenericNetworkConfigurator {
            @display("p=44.46,142.5");
        }

        radioMedium: IdealRadioMedium {
            @display("p=44,26");
        }

        Anchor1: RangingHost {
            @display("p=150,50;i=device/accesspoint");
            mobilityType = "StationaryMobility";
            nic.mac.address = "DE-AD-BE-EF-10-01";
        }

        Anchor2: RangingHost {
            @display("p=650,150;i=device/accesspoint");
            mobilityType = "StationaryMobility";
            nic.mac.address = "DE-AD-BE-EF-10-02";
        }

        Anchor3: RangingHost {
            @display("p=400,550;i=device/accesspoint");
            mobilityType = "StationaryMobility";
            nic.mac.address = "DE-AD-BE-EF-10-03";
        }

        Mobile1: RangingHost {
            @display("p=200,200");
            mobilityType = "LinearMobility";
            nic.mac.promiscuous = true;
        }
}
