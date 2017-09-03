/*   IPIN 2017 Localization Method Simulator
 *
 *   Copyright (C) 2017 Tomasz Jankowski
 *
 *   This program is free software; you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation; either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program; if not, write to the Free Software Foundation,
 *   Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301  USA
 */

#pragma once

#include <vector>

#include <omnetpp.h>
#include <MACAddress.h>
#include <Coord.h>
#include <IRadio.h>

#include "Listener.h"
#include "HardwareClockClient.h"

namespace ipin2017
{

class RangingHost :
    public HardwareClockClient
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
