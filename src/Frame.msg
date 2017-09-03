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

namespace ipin2017;

enum FrameType
{
    BEACON_FRAME = 1;
    RANGING_REPLY_FRAME = 2;
    WHISTLE_FRAME = 3;
}

packet Frame 
{
    unsigned int type @enum(FrameType) = 0;
    unsigned int sequenceNumber = 0;
    
    name = "Frame";
}
