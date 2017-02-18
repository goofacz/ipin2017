#pragma once

#include <memory>

#include <omnetpp.h>
#include <MACAddress.h>
#include <Coord.h>
#include <IRadio.h>

#include "RangingPacket_m.h"
#include "Listener.h"

namespace ipin2017
{

class RangingApplication :
    public omnetpp::cSimpleModule
{
    protected:
        struct RecentTransmitterTimestamps
        {
            omnetpp::simtime_t undefined = 0;
            omnetpp::simtime_t idle = 0;
            omnetpp::simtime_t transmitting = 0;
        };

        struct RecentReceiverTimestamps
        {
            omnetpp::simtime_t undefined = 0;
            omnetpp::simtime_t idle = 0;
            omnetpp::simtime_t busy = 0;
            omnetpp::simtime_t receiving = 0;
        };

    protected:
        virtual void transmissionStateChanged (inet::physicallayer::IRadio::TransmissionState state);

        virtual void receptionStateChanged (inet::physicallayer::IRadio::ReceptionState state);

        void initialize (int stage) override;

        const inet::MACAddress& getLocalAddress () const;

        void sendMacPacket (const inet::MACAddress& destinationAddress,
                            std::unique_ptr<RangingPacket> packet,
                            unsigned int delay = 0,
                            omnetpp::SimTimeUnit delay_unit = omnetpp::SIMTIME_MS);

        void scheduleSelfMessage (std::unique_ptr<omnetpp::cMessage> message,
                                  unsigned int delay,
                                  omnetpp::SimTimeUnit delay_unit);

        const RecentTransmitterTimestamps& getRecentTransmitterTimestamps () const;

        const RecentReceiverTimestamps& getRRecentReceiverTimestamps () const;

        const inet::Coord& getCurrentPosition () const;

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
        RecentTransmitterTimestamps recentTransmitterTimestamps;
        RecentReceiverTimestamps recentReceiverTimestamps;
};

} // namespace ipin2017
