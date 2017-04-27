package ipin2017.simulations;

import ipin2017.RangingHost;
import inet.networklayer.configurator.generic.GenericNetworkConfigurator;
import inet.physicallayer.idealradio.IdealRadioMedium;
import inet.visualizer.integrated.IntegratedCanvasVisualizer;

network StationaryNetwork
{
    parameters:
        @display("bgb=700,700");
        int mobilesNumber = default(0);

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
            @display("p=650,100;i=device/accesspoint");
            mobilityType = "StationaryMobility";
            nic.mac.address = "DE-AD-BE-EF-10-02";
        }

        Anchor3: RangingHost {
            @display("p=400,550;i=device/accesspoint");
            mobilityType = "StationaryMobility";
            nic.mac.address = "DE-AD-BE-EF-10-03";
        }
		
		//
		// Mobile nodes
		//
        Mobiles[mobilesNumber]: RangingHost {
            @display("p=300,300");
            nic.mac.promiscuous = true;
            mobilityType = "StaticGridMobility";
        }

//        Mobile1: RangingHost {
//            @display("p=150,150");
//            mobilityType = "LinearMobility";
//            nic.mac.address = "DE-AD-BE-EF-00-01";
//            nic.mac.promiscuous = true;
//        }
//        
//        Mobile2: RangingHost {
//            @display("p=250,150");
//            mobilityType = "LinearMobility";
//            nic.mac.address = "DE-AD-BE-EF-00-02";
//            nic.mac.promiscuous = true;
//        }
//        
//        Mobile3: RangingHost {
//            @display("p=350,150");
//            mobilityType = "LinearMobility";
//            nic.mac.address = "DE-AD-BE-EF-00-03";
//            nic.mac.promiscuous = true;
//        }
//        
//        Mobile4: RangingHost {
//            @display("p=450,150");
//            mobilityType = "LinearMobility";
//            nic.mac.address = "DE-AD-BE-EF-00-04";
//            nic.mac.promiscuous = true;
//        }
//        
//        Mobile5: RangingHost {
//            @display("p=550,150");
//            mobilityType = "LinearMobility";
//            nic.mac.address = "DE-AD-BE-EF-00-05";
//            nic.mac.promiscuous = true;
//        }
//        
//        Mobile6: RangingHost {
//            @display("p=150,250");
//            mobilityType = "LinearMobility";
//            nic.mac.address = "DE-AD-BE-EF-00-06";
//            nic.mac.promiscuous = true;
//        }
//        
//        Mobile7: RangingHost {
//            @display("p=250,250");
//            mobilityType = "LinearMobility";
//            nic.mac.address = "DE-AD-BE-EF-00-07";
//            nic.mac.promiscuous = true;
//        }
//        
//        Mobile8: RangingHost {
//            @display("p=350,250");
//            mobilityType = "LinearMobility";
//            nic.mac.address = "DE-AD-BE-EF-00-08";
//            nic.mac.promiscuous = true;
//        }
//        
//        Mobile9: RangingHost {
//            @display("p=450,250");
//            mobilityType = "LinearMobility";
//            nic.mac.address = "DE-AD-BE-EF-00-09";
//            nic.mac.promiscuous = true;
//        }
//        
//        Mobile10: RangingHost {
//            @display("p=550,250");
//            mobilityType = "LinearMobility";
//            nic.mac.address = "DE-AD-BE-EF-00-0A";
//            nic.mac.promiscuous = true;
//        }
//        
//        Mobile11: RangingHost {
//            @display("p=150,350");
//            mobilityType = "LinearMobility";
//            nic.mac.address = "DE-AD-BE-EF-00-0B";
//            nic.mac.promiscuous = true;
//        }
//        
//        Mobile12: RangingHost {
//            @display("p=250,350");
//            mobilityType = "LinearMobility";
//            nic.mac.address = "DE-AD-BE-EF-00-0C";
//            nic.mac.promiscuous = true;
//        }
//        
//        Mobile13: RangingHost {
//            @display("p=350,350");
//            mobilityType = "LinearMobility";
//            nic.mac.address = "DE-AD-BE-EF-00-0D";
//            nic.mac.promiscuous = true;
//        }
//        
//        Mobile14: RangingHost {
//            @display("p=450,350");
//            mobilityType = "LinearMobility";
//            nic.mac.address = "DE-AD-BE-EF-00-0E";
//            nic.mac.promiscuous = true;
//        }
//        
//        Mobile15: RangingHost {
//            @display("p=550,350");
//            mobilityType = "LinearMobility";
//            nic.mac.address = "DE-AD-BE-EF-00-0F";
//            nic.mac.promiscuous = true;
//        }
//        
//        Mobile16: RangingHost {
//            @display("p=150,450");
//            mobilityType = "LinearMobility";
//            nic.mac.address = "DE-AD-BE-EF-00-10";
//            nic.mac.promiscuous = true;
//        }
//        
//        Mobile17: RangingHost {
//            @display("p=250,450");
//            mobilityType = "LinearMobility";
//            nic.mac.address = "DE-AD-BE-EF-00-11";
//            nic.mac.promiscuous = true;
//        }
//        
//        Mobile18: RangingHost {
//            @display("p=350,450");
//            mobilityType = "LinearMobility";
//            nic.mac.address = "DE-AD-BE-EF-00-12";
//            nic.mac.promiscuous = true;
//        }
//        
//        Mobile19: RangingHost {
//            @display("p=450,450");
//            mobilityType = "LinearMobility";
//            nic.mac.address = "DE-AD-BE-EF-00-13";
//            nic.mac.promiscuous = true;
//        }
//        
//        Mobile20: RangingHost {
//            @display("p=550,450");
//            mobilityType = "LinearMobility";
//            nic.mac.address = "DE-AD-BE-EF-00-14";
//            nic.mac.promiscuous = true;
//        }
}