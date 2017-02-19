#pragma once

#include <omnetpp.h>
#include <MACAddress.h>
#include <Coord.h>
#include <IRadio.h>

#include "Listener.h"

namespace ipin2017
{

class RangingHost :
    public omnetpp::cModule
{
    public:
        const inet::MACAddress& getLocalAddress () const;

        const omnetpp::SimTime& getTxBeginTimestamp () const;

        const omnetpp::SimTime& getRxBeginTimestamp () const;

        const inet::Coord& getCurrentPosition () const;

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
        inet::physicallayer::IRadio::TransmissionState txCurrentState {inet::physicallayer::IRadio::TRANSMISSION_STATE_UNDEFINED};
        inet::physicallayer::IRadio::ReceptionState rxCurrentState {inet::physicallayer::IRadio::RECEPTION_STATE_UNDEFINED};
        omnetpp::SimTime txBeginTimestamp {0};
        omnetpp::SimTime rxBeginTimestamp {0};
};

} // namespace ipin2017
