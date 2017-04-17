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

package ipin2017;

import inet.examples.mobility.MobileHost;
import inet.linklayer.ideal.IdealWirelessNic;
import inet.networklayer.common.InterfaceTable;
import inet.networklayer.generic.GenericRoutingTable;

module RangingHost extends MobileHost
{
    parameters:
        @class(RangingHost);
        @networkNode();
        *.interfaceTableModule = default(absPath(".interfaceTable"));

        string clockType = default("");
        string applicationType = default("");

    gates:
        input radioIn @directIn;

    submodules:
        interfaceTable: InterfaceTable;

        routingTable: GenericRoutingTable;

        nic: IdealWirelessNic;

        clock : <clockType> like IHardwareClock;
        
        application: <applicationType> like IRangingApplication;

    connections:
        radioIn --> nic.radioIn;
        
        nic.upperLayerIn <-- application.out;
        nic.upperLayerOut --> application.in;
}