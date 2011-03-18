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

#ifndef AGGREGATOR_H
#define AGGREGATOR_H

#include "ns3/object.h"
#include <vector>
#include <string>

namespace ns3 {
/**
 * This is a base class for aggregators, which are classes that 
 * consolidate inputs from one or more sources and dispatches
 * them to some output mechanism. Aggregators will let any 
 * and all reported data pass through to the output. If users want to 
 * disable the logging of data from one particular source, they must 
 * control that source. Disabling the Aggregator stops logging for
 * all input sources.
 */

class Aggregator : public DataCollection
{
public:
	static TypeId GetTypeId ();

	Aggregator ();
	virtual ~Aggregator () {};

	void SetInputSource(Prt<DataCollection> source, std::string name);

private:
	vector<Ptr<DataCollection>> m_sources;

}; // class Aggregator


} // namespace ns3

#endif // AGGREGATOR_H
