#pragma once

#define EXPECT(condition, message)                                             \
    if (!(condition))                                                          \
    {                                                                          \
        EV << __FILE__ << " at line " << __LINE__ << (message) << std::endl;   \
        throw cRuntimeError (message);                                         \
    }
