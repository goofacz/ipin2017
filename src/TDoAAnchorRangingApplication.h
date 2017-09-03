/*   IPIN 2017 Localization Method Simulator
 *
 *   Copyright (C) 2017 Tomasz Jankowski
 *
 *   This program is free software; you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation; either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program; if not, write to the Free Software Foundation,
 *   Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301  USA
 */

#pragma once

#include <fstream>
#include <omnetpp.h>
#include <IRadio.h>

#include "RangingApplication.h"
#include "BeaconFrame_m.h"

namespace ipin2017
{

class TDoAAnchorRangingApplication :
    public RangingApplication
{
  private:
    void initialize(int stage) override;

    void finish() override;

    void handleMessage (omnetpp::cMessage* message) override;

    void handlFrame (BeaconFrame* frame);

    void handleSelfMessage ();

    unsigned int getCurrentPacketSequenceNumber () const;

    unsigned int getNextPacketSequenceNumber ();

    void sendBeaconFrame ();

    void onRxStateChangedCallback (inet::physicallayer::IRadio::ReceptionState state);

    omnetpp::SimTime broadcastBeaconDelay {0};
    inet::MACAddress echoAnchorAddress;
    omnetpp::SimTime echoBeaconDelay {0};
    unsigned int packetSequenceNumberGenerator {0};
    omnetpp::SimTime beaconReceptionTimestamp {0};
};

}; // namespace ipin2017
