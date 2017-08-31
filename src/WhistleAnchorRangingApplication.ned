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

//
// Application implementing anchor side of Whistle localization method.
//
simple WhistleAnchorRangingApplication extends RangingApplication
{
	parameters:
	    @class(WhistleAnchorRangingApplication);
	    
	    // Whether anchor is a base node.
	    bool isBaseAnchor = default(false);
	    
	    // Delay after which anchor will transmit it's message.
	    int echoFrameDelay @unit(ps) = default(35ms);
	    
	    // File name in which measurements will be stored (do not set manually).
	    string resultsFileName = default("");
	    
}