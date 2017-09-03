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

#include <vector>
#include <memory>

#include <omnetpp.h>
#include <IRadio.h>

#include "RangingApplication.h"
#include "WhistleFrame_m.h"

namespace ipin2017
{

class WhistleAnchorRangingApplication :
    public RangingApplication
{
  private:
    struct RecordedFrame
    {
        RecordedFrame () = default;

        RecordedFrame (std::unique_ptr<const WhistleFrame> frame,
                       const omnetpp::SimTime& receptionTimestamp,
                       const omnetpp::SimTime& transmissionTimestamp,
                       const inet::Coord& anchorPosition,
                       const inet::Coord& mobilePosition);

        std::unique_ptr<const WhistleFrame> frame {nullptr};
        omnetpp::SimTime receptionTimestamp {0};
        omnetpp::SimTime transmissionTimestamp {0};
        inet::Coord anchorPosition;
        inet::Coord mobilePosition;
    };

  private:
    void initialize (int stage) override;

    void finish () override;

    void handleMessage (omnetpp::cMessage* message) override;

    void onRxStateChangedCallback (inet::physicallayer::IRadio::ReceptionState state);

    void onTxStateChangedCallback (inet::physicallayer::IRadio::TransmissionState state);

    void handleSelfMessage (cMessage* message);

    void handleMessage (const WhistleFrame* message);

    bool isBaseAnchor {false};
    omnetpp::SimTime echoFrameDelay {0};
    omnetpp::SimTime frameReceptionTimestamp {0};
    std::vector<RecordedFrame> recordedFrames;
    std::unique_ptr<WhistleFrame> scheduledEchoFrame;
};

}; // namespace ipin2017
