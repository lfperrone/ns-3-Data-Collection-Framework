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

#ifndef PROBE_FACTORY_H
#define PROBE_FACTORY_H

#include "ns3/object.h"
#include "ns3/ptr.h"

namespace ns3 {

	class Probe;

	class ProbeFactory : public Object {
	public:
		static TypeId GetTypeId (void);

		ProbeFactory ();

		/**
		 * \return smart pointer to Probe
		 *
		 * Abstract class for creating instances of probes
		 */
		virtual Ptr<Probe> CreateProbe() = 0;

	}; // class ProbeFactory

} // namespace ns3

#endif // PROBE_FACTORY_H
