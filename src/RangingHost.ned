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

package ipin2017;

import inet.examples.mobility.MobileHost;
import inet.linklayer.ideal.IdealWirelessNic;
import inet.networklayer.common.InterfaceTable;
import inet.networklayer.generic.GenericRoutingTable;

//
// Component representing wireless node. Can be configred to be either mobile or anchor node.
//
module RangingHost extends MobileHost
{
    parameters:
        @class(RangingHost);
        @networkNode();
        *.interfaceTableModule = default(absPath(".interfaceTable"));

		// Desired clock type to by used by node. Possible values are: "NoneDrift", "ConstantDrift", 
		// "BoundedDrift" and "BoundedDriftVariation".
        string clockType = default("");
        
        // Desired application to be run on node. Possible values are: "WhistleAnchorRangingApplication", 
        // "WhistleMobileRangingApplication", "TDoAMobileRangingApplication" and "TDoAAnchorRangingApplication".
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