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

#include "data-collection.h"

namespace ns3 {
		static TypeId GetTypeId ();

    DataCollection::DataCollection ();
		virtual DataCollection::~DataCollection ();
		virtual void DataCollection::AddIntSample (std::string context, time t, int64_t value) = 0;

		virtual void DataCollection::AddDoubleSample (std::string context, time t, double value) = 0;

    Ptr<DataCollection> DataCollection::GetParent (void);
    void DataCollection::SetParent<DataCollection> (Ptr<DataCollection> parent);

	private:
		Ptr<DataCollection> m_parent;

	}; // class DataCollection

} // namespace ns3

#endif // DATA_COLLECTION_H
