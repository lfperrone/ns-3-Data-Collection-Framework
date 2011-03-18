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

#ifndef PROBE_HELPER_H
#define PROBE_HELPER_H

#include "ns3/ptr.h"
#include "ns3/object.h"
#include "ns3/object-factory.h"
#include "ns3/trace-helper.h"

#include "probe.h"
#include "collector.h"

namespace ns3 {

	class ProbeHelper
	{
		public:
      enum CollectorMode 
			{
				COLLECTOR_STREAM, /** dump data to standard output **/
				COLLECTOR_FRAMEWORK /** send data to automation framework **/
			};
			
			static TypeId GetTypeId ();
			
			ProbeHelper();
			virtual ~ProbeHelper ();

			// need a method to flush all probes at termination?

			bool GetProbeGlobalStatus (void) const;
			void SetProbeGlobalStatus (bool enable);
		
		private:
			std::vector< Ptr<Probe> > m_probes;
	};

} // namespace ns3

#endif // PROBE_HELPER_H
