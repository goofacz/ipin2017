/*
    Clock Synchronization Simulation in OMNet++
    Copyright (C) 2012 Jens Steinhauser

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along
    with this program; if not, write to the Free Software Foundation, Inc.,
    51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
*/

#include <cassert>
#include <exception>

#include "HardwareClockClient.h"
#include "HardwareClock.h"

using namespace omnetpp;

namespace ipin2017
{

HardwareClockClient::HardwareClockClient()
	: _clock(NULL)
{
}

void HardwareClockClient::scheduleAtHWtime(const simtime_t& time, cMessage* msg)
{
	assert (NULL != _clock);
	_clock->scheduleAtHWtime(time, msg, this);
}

omnetpp::simtime_t HardwareClockClient::getHWtime () const
{
    assert (NULL != _clock);
    return _clock->getHWtime();
}

void HardwareClockClient::scheduleAtInObject(const simtime_t realtime, cMessage* msg)
{
	Enter_Method_Silent();
	take(msg);

	scheduleAt(realtime, msg);
}

void HardwareClockClient::setHardwareClock(HardwareClock* clock)
{
    assert (NULL == _clock);
	_clock = clock;
}

} // namespace ipin2017
