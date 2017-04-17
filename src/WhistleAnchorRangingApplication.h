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
    struct ReceivedFrame
    {
        ReceivedFrame () = default;

        ReceivedFrame (std::unique_ptr<const WhistleFrame> frame,
                       const omnetpp::SimTime& receptionTimestamp,
                       const omnetpp::SimTime& transmissionTimestamp);

        std::unique_ptr<const WhistleFrame> frame {nullptr};
        omnetpp::SimTime receptionTimestamp {0};
        omnetpp::SimTime transmissionTimestamp {0};
    };

  private:
    void initialize (int stage) override;

    void finish () override;

    void handleMessage (omnetpp::cMessage* message) override;

    void onRxStateChangedCallback (inet::physicallayer::IRadio::ReceptionState state);

    void handleSelfMessage (cMessage* message);

    void handleMessage (const WhistleFrame* message);

    bool isBaseAnchor {false};
    omnetpp::SimTime echoFrameDelay {0};
    omnetpp::SimTime frameReceptionTimestamp {0};
    std::vector<ReceivedFrame> receivedFrames;
    std::unique_ptr<WhistleFrame> scheduledEchoFrame;
};

}; // namespace ipin2017
