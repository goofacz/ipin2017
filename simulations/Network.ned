//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

package ipin2017.simulations;

import ipin2017.AnchorRangingHost;
import ipin2017.MobileRangingHost;
import inet.networklayer.configurator.generic.GenericNetworkConfigurator;
import inet.physicallayer.idealradio.IdealRadioMedium;
import inet.visualizer.integrated.IntegratedCanvasVisualizer;

//
// Two instances (tic and toc) of Txc connected.
//
network Network
{
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
        
        Anchor1: AnchorRangingHost {
            @display("p=291,136");
        }
        
        Anchor2: AnchorRangingHost {
            @display("p=510,136");
        }

        Anchor3: AnchorRangingHost {
            @display("p=291,348");
        }

        Anchor4: AnchorRangingHost {
            @display("p=510,348");
        }

        Mobile1: MobileRangingHost {
            @display("p=873,235");
        }
}
