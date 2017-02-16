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

module HelperAnchorRangingHost extends RangingHost
{
    parameters:
        @display("i=device/accesspoint");

	    int backhaulOutSize = default(0);

        mobilityType = "StationaryMobility";
        applicationType = "HelperAnchorRangingApplication";
        nic.mac.promiscuous = true;
	    application.backhaulOutSize = backhaulOutSize;

    gates:
        output backhaulOut[backhaulOutSize] @loose;

    connections:
        for i=0..sizeof(backhaulOut)-1 {
            application.backhaulOut[i] --> backhaulOut[i];
        }
}