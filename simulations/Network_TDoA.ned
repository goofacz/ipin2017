package ipin2017.simulations;

import ipin2017.TDoAAnchorRangingHost;
import ipin2017.MobileRangingHost;
import inet.networklayer.configurator.generic.GenericNetworkConfigurator;
import inet.physicallayer.idealradio.IdealRadioMedium;
import inet.visualizer.integrated.IntegratedCanvasVisualizer;

network Network_TDoA
{
    parameters:
	    @display("bgb=908,390");

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
        
        Anchor1: TDoAAnchorRangingHost {
            @display("p=291,136");
            nic.mac.address = "DE-AD-BE-EF-10-01";
            application.broadcastBeaconDelay = 5s;
        }
        
        Anchor2: TDoAAnchorRangingHost {
            @display("p=510,136");
            nic.mac.address = "DE-AD-BE-EF-10-02";
            application.echoAnchorAddress = "DE-AD-BE-EF-10-01";
        }

        Anchor3: TDoAAnchorRangingHost {
            @display("p=510,348");
            nic.mac.address = "DE-AD-BE-EF-10-03";
            application.echoAnchorAddress = "DE-AD-BE-EF-10-02";
        }

        Anchor4: TDoAAnchorRangingHost {
            @display("p=291,348");
            nic.mac.address = "DE-AD-BE-EF-10-04";
            application.echoAnchorAddress = "DE-AD-BE-EF-10-03";
        }

        Mobile1: MobileRangingHost {
            @display("p=345,300");
            applicationType = "TDoAMobileRangingApplication";
            nic.mac.address = "DE-AD-BE-EF-00-01";
            nic.mac.promiscuous = true;
        }
}