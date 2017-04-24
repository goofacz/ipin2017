package ipin2017.simulations;

import ipin2017.RangingHost;
import inet.networklayer.configurator.generic.GenericNetworkConfigurator;
import inet.physicallayer.idealradio.IdealRadioMedium;
import inet.visualizer.integrated.IntegratedCanvasVisualizer;

network MovingNetwork
{
    parameters:
	    @display("bgb=908,450");

    submodules:
        visualizer: IntegratedCanvasVisualizer {
            @display("p=128,24");
        }

        configurator: GenericNetworkConfigurator {
            @display("p=219,24");
        }
        
        radioMedium: IdealRadioMedium {
            @display("p=44,26");
        }
        
        Anchor1: RangingHost {
            @display("p=300,100;i=device/accesspoint");
            mobilityType = "StationaryMobility";
            nic.mac.address = "DE-AD-BE-EF-10-01";
        }
        
        Anchor2: RangingHost {
            @display("p=500,50;i=device/accesspoint");
            mobilityType = "StationaryMobility";
            nic.mac.address = "DE-AD-BE-EF-10-02";
        }

        Anchor3: RangingHost {
            @display("p=400,350;i=device/accesspoint");
            mobilityType = "StationaryMobility";
            nic.mac.address = "DE-AD-BE-EF-10-03";
        }

        Mobile1: RangingHost {
            @display("p=200,200");
            mobilityType = "LinearMobility";
            nic.mac.address = "DE-AD-BE-EF-00-01";
            nic.mac.promiscuous = true;
        }
}