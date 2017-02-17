#pragma once

#include <cassert>
#include <functional>

#include <omnetpp.h>

namespace ipin2017
{

template<typename T>
class Listener :
    public omnetpp::cListener
{
public:
    using Callback = std::function<void(omnetpp::cComponent*, omnetpp::simsignal_t, T, omnetpp::cObject*)>;

    public:
        explicit Listener (Callback callback = nullptr);

        Listener& operator = (Callback newCallback);

        void receiveSignal (omnetpp::cComponent* source,
                            omnetpp::simsignal_t signalID,
                            T value,
                            omnetpp::cObject* details) override;

    private:
        Callback callback;
};

template<typename T>
Listener<T>::Listener (Callback callback) :
    callback {std::move (callback)}
{
    // ...
}

template<typename T>
Listener<T>& Listener<T>::operator = (Callback newCallback)
{
    callback = std::move (newCallback);
    return *this;
}

template<typename T>
void
Listener<T>::receiveSignal (omnetpp::cComponent* source,
                            omnetpp::simsignal_t signalID,
                            T value,
                            omnetpp::cObject* details)
{
    assert (callback);
    callback (source, signalID, value, details);
}

} // namespace ipin2017
