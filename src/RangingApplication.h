#pragma once

#include <memory>

#include <omnetpp.h>
#include <MACAddress.h>

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

    private:
        int numInitStages () const override;

        void transmissionStateChangedCallback (cComponent* source,
                                               simsignal_t signalID,
                                               long value,
                                               cObject* details);

        void receptionStateChangedCallback (cComponent* source,
                                            simsignal_t signalID,
                                            long value,
                                            cObject* details);

        inet::MACAddress localAddress;
        Listener<long> transmissionStateChangedListener;
        Listener<long> receptionStateChangedListener;
        RecentTransmitterTimestamps recentTransmitterTimestamps;
        RecentReceiverTimestamps recentReceiverTimestamps;
};

} // namespace ipin2017
