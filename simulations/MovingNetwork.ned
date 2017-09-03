//   IPIN 2017 Localization Method Simulator
// 
//   Copyright (C) 2017 Tomasz Jankowski
//   
//   This program is free software; you can redistribute it and/or modify
//   it under the terms of the GNU General Public License as published by
//   the Free Software Foundation; either version 3 of the License, or
//   (at your option) any later version.
//      
//   This program is distributed in the hope that it will be useful,
//   but WITHOUT ANY WARRANTY; without even the implied warranty of
//   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//   GNU General Public License for more details.
//      
//   You should have received a copy of the GNU General Public License
//   along with this program; if not, write to the Free Software Foundation,
//   Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301  USA

package ipin2017.simulations;

import ipin2017.RangingHost;
import inet.networklayer.configurator.generic.GenericNetworkConfigurator;
import inet.physicallayer.idealradio.IdealRadioMedium;
import inet.visualizer.integrated.IntegratedCanvasVisualizer;

//
// Initial configuration for test cases involving single moving mobile node.
//
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
