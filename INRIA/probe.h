/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2010 Bucknell University
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation;
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * Author: L. Felipe Perrone (perrone@bucknell.edu)
 */

#ifndef PROBE_H
#define PROBE_H

#include "ns3/object.h"
#include "ns3/nstime.h"

namespace ns3 {
	
	class Probe : public Object {
	public:
		static TypeId GetTypeId ();
		Probe ();
		virtual ~Probe();

 /**
   * This method wraps the creation of probes that is performed
   * by a probe factory based on a TypeId.
   */
		static Ptr<Probe> CreateProbe(Ptr<Object> owner, TypeId tid);

		virtual bool GetProbeStatus (void) const = 0;
		virtual void SetProbeStatus (bool enabled) = 0;

		virtual void Set (Time start, Time stop, Time interval);
		virtual void SetStartTime (Time start);
		virtual void SetStopTime (Time stop);
		virtual void SetIntervalTime (Time interval);
		
	protected:
		bool m_status;
		Time m_start;
		Time m_stop;
		Time m_interval;

	}; // class ProbeFactory

} // namespace ns3

#endif // PROBE_H
