#include "BackhaulMessage.h"

using namespace omnetpp;

namespace ipin2017
{

Register_Class(BackhaulMessage);

BackhaulMessage::BackhaulMessage (const char *name, int kind) :
    BackhaulMessage_Base (name, kind)
{
    frame = nullptr;
}

BackhaulMessage::BackhaulMessage (const BackhaulMessage& other) :
    BackhaulMessage_Base (other)
{
    frame = nullptr;
    copy (other);
}

BackhaulMessage::~BackhaulMessage ()
{
    if (frame)  {
        delete frame;
    }
}

BackhaulMessage&
BackhaulMessage::operator = (const BackhaulMessage& other)
{
    if (this == &other) {
        return *this;
    }
    
    BackhaulMessage_Base::operator = (other);
    copy (other);

    return *this;
}

BackhaulMessage*
BackhaulMessage::dup() const
{
    return new BackhaulMessage (*this);
}

void
BackhaulMessage::copy (const BackhaulMessage& other)
{
    if (frame)    {
        delete frame;
    }

    if (other.frame)    {
        frame = other.frame->dup ();
    }
    else    {
        frame = nullptr;
    }
}

} // namespace ipin2017
