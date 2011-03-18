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

#ifndef AGGREGATOR_CSV_H
#define AGGREGATOR_CSV_H

#include "ns3/object.h"
#include <vector>
#include <string>

namespace ns3 {

/**
 * This aggregator produces a text file as output. The values
 * logged into this object will appear separated by commas in the 
 * output file (i.e. as in a CSV file).
 **/	
class AggregatorCSV : public AggregatorFile
{
public:
	static TypeId GetTypeId ();

	AggregatorCSV ();
	virtual ~AggregatorCSV () {};

  virtual void IntToOutput(std::string s, Time t, int v);
	virtual void DoubleToOutput(std::string s, Time t, double v);
	virtual void StringIntToOutput(std::string s, Time t, std::string v);

}; // class AggregatorCSV


} // namespace ns3

#endif // AGGREGATOR_H
