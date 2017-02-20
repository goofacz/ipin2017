#include <cassert>
#include <memory>

#include <INETDefs.h>
#include <HelperAnchorRangingApplication.h>
#include <MACAddress.h>


using namespace inet;
using namespace omnetpp;
using namespace std;

namespace ipin2017
{

Define_Module(HelperAnchorRangingApplication);

void
HelperAnchorRangingApplication::initialize(int stage)
{
    RangingApplication::initialize(stage);

    if (stage == INITSTAGE_APPLICATION_LAYER)
    {
        // TODO
    }
}

void
HelperAnchorRangingApplication::handleMessage (cMessage* message)
{
    if (message->isSelfMessage ())
    {
        // TODO
    }
    else
    {
        const auto frame = check_and_cast<const Frame*> (message);
        switch (frame->getType ())
        {
            case BEACON_FRAME:
                handleFrame (check_and_cast<BeaconFrame*> (message));
                break;
            case RANGING_REPLY_FRAME:
                handleFrame (check_and_cast<RangingReplyFrame*> (message));
                break;
            default:
                throw cRuntimeError ("Unsupported frame");
        }
    }

    delete message;
}

void
HelperAnchorRangingApplication::handleFrame (RangingReplyFrame* message)
{
    // TODO
}

void
HelperAnchorRangingApplication::handleFrame (BeaconFrame* message)
{
    // TODO
}

}; // namespace ipin2017
