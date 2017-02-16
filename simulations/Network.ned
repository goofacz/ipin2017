package ipin2017.simulations;

import ipin2017.MasterAnchorRangingHost;
import ipin2017.HelperAnchorRangingHost;
import ipin2017.MobileRangingHost;
import inet.networklayer.configurator.generic.GenericNetworkConfigurator;
import inet.physicallayer.idealradio.IdealRadioMedium;
import inet.visualizer.integrated.IntegratedCanvasVisualizer;

network Network
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
        
        Anchor1: MasterAnchorRangingHost {
            @display("p=291,136");
            nic.mac.address = "DE-AD-BE-EF-10-01";
        }
        
        Anchor2: HelperAnchorRangingHost {
            @display("p=510,136");
            nic.mac.address = "DE-AD-BE-EF-10-02";
        }

        Anchor3: HelperAnchorRangingHost {
            @display("p=291,348");
            nic.mac.address = "DE-AD-BE-EF-10-03";
        }

        Anchor4: HelperAnchorRangingHost {
            @display("p=510,348");
            nic.mac.address = "DE-AD-BE-EF-10-04";
        }

        Mobile1: MobileRangingHost {
            @display("p=673,300");
            nic.mac.address = "DE-AD-BE-EF-00-01";
        }
}