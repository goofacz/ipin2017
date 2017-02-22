#pragma once

#include <vector>

#include <omnetpp.h>
#include <MACAddress.h>
#include <Coord.h>
#include <IRadio.h>

#include "Listener.h"

namespace ipin2017
{

class RangingHost :
    public omnetpp::cSimpleModule
{
    public:
        using TxStateChangedCallback = std::function<void(inet::physicallayer::IRadio::TransmissionState)>;
        using RxStateChangedCallback = std::function<void(inet::physicallayer::IRadio::ReceptionState)>;

    public:
        const inet::MACAddress& getLocalAddress () const;

        const inet::Coord& getCurrentPosition () const;

        void addTxStateChangedCallback (TxStateChangedCallback callback);

        void addRxStateChangedCallback (RxStateChangedCallback callback);

    protected:
        void initialize (int stage) override;

    private:
        int numInitStages () const override;

        void transmissionStateChangedCallback (omnetpp::cComponent* source,
                                               omnetpp::simsignal_t signalID,
                                               long value,
                                               omnetpp::cObject* details);

        void receptionStateChangedCallback (omnetpp::cComponent* source,
                                            simsignal_t signalID,
                                            long value,
                                            omnetpp::cObject* details);

        void mobilityStateChangedCallback (omnetpp::cComponent* source,
                                           simsignal_t signalID,
                                           omnetpp::cObject* value,
                                           omnetpp::cObject* details);

        inet::MACAddress localAddress;
        inet::Coord currentPosition;

        Listener<long> transmissionStateChangedListener;
        Listener<long> receptionStateChangedListener;
        Listener<omnetpp::cObject*> mobilityStateChangedListener;

        std::vector<TxStateChangedCallback> txStateChangedcallbacks;
        std::vector<RxStateChangedCallback> rxStateChangedcallbacks;
};

} // namespace ipin2017
