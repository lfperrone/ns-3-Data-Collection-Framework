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

#ifndef AGGREGATOR_FILE_H
#define AGGREGATOR_FILE_H

#include "ns3/object.h"
#include "aggregator.h"

namespace ns3 {

/**
 * This aggregator produces a simple text file as output. The values
 * logged into this object will appear separated by spaces in the 
 * output file. Use this class to derive other aggregators that
 * record output in files.
 **/
class AggregatorFile : public Aggregator
{
public:
	static TypeId GetTypeId ();

	AggregatorFile ();
	virtual ~AggregatorFile () {};

	void OpenOutput(std::string fileName);
  void CloseOutput();

	virtual void IntToOutput(std::string s, Time t, int v);
	virtual void DoubleToOutput(std::string s, Time t, double v);
	virtual void StringIntToOutput(std::string s, Time t, std::string v);

private:
	std::string m_filename;
  std::ofstream m_outfile;

}; // class AggregatorFile

} // namespace ns3

#endif // AGGREGATOR_FILE_H
