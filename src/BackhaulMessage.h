#pragma once

#include "BackhaulMessage_m.h"

namespace ipin2017
{

class BackhaulMessage : public BackhaulMessage_Base
{
    public:
        BackhaulMessage (const char *name=nullptr, int kind=0);

        BackhaulMessage (const BackhaulMessage& other);

        ~BackhaulMessage ();

        BackhaulMessage& operator = (const BackhaulMessage& other);

        BackhaulMessage* dup () const override;

        void setFrame(const FramePointer& frame) override;

    private:
        void copy (const BackhaulMessage& other);
};

} // namespace ipin2017
