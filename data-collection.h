/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2011 Bucknell University
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

#ifndef DATA_COLLECTION_H
#define DATA_COLLECTION_H

#include "ns3/object.h"

namespace ns3 {
	
	/** 
	 * Abstract class for collectors.
	 */

	class DataCollection : public Object {
	public:
		static TypeId GetTypeId (void);

		DataCollection ();
		virtual ~DataCollection ();

		/**
		 * Add a new integer sample to the collector, recording the time of its
		 * creation.
		 */
		virtual void AddIntSample (std::string context, time t, int64_t value) = 0;

		/**
		 * Add a new double sample to the collector, recording the time of its
		 * creation.
		 */
		virtual void AddDoubleSample (std::string context, time t, double value) = 0;

    Ptr<DataCollection> GetParent (void);
    void SetParent<DataCollection> (Ptr<DataCollection> parent);

		virtual void EnableReporting ();
		virtual void DisableReporting ();

	private:
		bool m_enabled;
		Ptr<DataCollection> m_parent;

	}; // class DataCollection

} // namespace ns3

#endif // DATA_COLLECTION_H
