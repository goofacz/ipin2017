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

import ipin2017.RangingHost;
import inet.networklayer.configurator.generic.GenericNetworkConfigurator;
import inet.physicallayer.idealradio.IdealRadioMedium;
import inet.visualizer.integrated.IntegratedCanvasVisualizer;

//
// Two instances (tic and toc) of Txc connected.
//
network Network
{
    submodules:
        visualizer: IntegratedCanvasVisualizer {
            @display("p=580,125");
        }
        
        configurator: GenericNetworkConfigurator;
        
        radioMedium: IdealRadioMedium;
        
        hostA: RangingHost	{
            @display("p=50,325");
            application.sendMsgOnInit = true;
        }
        
        hostB: RangingHost	{
            @display("p=350,325");
        }
        
        hostC: RangingHost	{
            @display("p=250,325");
        }
}
