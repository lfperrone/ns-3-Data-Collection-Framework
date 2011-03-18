/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2010 IITP RAS
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
 * This is a proof of consept script for the Data Collection Framewotk API proposal
 *
 * Authors: Pavel Boyko <boyko@iitp.ru>
 *          Kirill Andreev <andreev@iitp.ru>
 */
#include "csv-collector.h"

namespace ns3 
{

CsvCollector::ProbeDescriptor::ProbeDescriptor (Ptr<Probe> probe, std::string name)
      : m_probe (probe), m_of (name.c_str ())
{
  if (! m_of.is_open()) NS_FATAL_ERROR ("Can't open output file \"" << name << "\"");
}

CsvCollector::ProbeDescriptor::~ProbeDescriptor ()
{
  m_of.close ();
}

TypeId
CsvCollector::GetTypeId ()
{
  static TypeId tid = TypeId ("ns3::CsvCollector")
    .SetParent<Object> ()
    .AddConstructor<CsvCollector> ()
    ;
  return tid;
}

CsvCollector::CsvCollector ()
{
}

CsvCollector::~CsvCollector ()
{
  for (ProbeMap::iterator i = m_probes.begin (); i != m_probes.end (); i ++)
  {
    delete i->second;
  }
  m_probes.clear ();
}

void
CsvCollector::AddDoubleProbe (Ptr<DoubleProbe> p, std::string probeName)
{
  // check that no probeName already registered
  NS_ASSERT (m_probes.find (probeName) == m_probes.end());

  // Connect to probe "Output" trace source
  p->TraceConnect ("Output", probeName, MakeCallback (&CsvCollector::PrintDoubleProbe , this));

  // Remember probe
  ProbeDescriptor*  desc  = new ProbeDescriptor (p, probeName + ".csv");
  m_probes.insert (std::make_pair (probeName, desc));
  desc->m_of << "time,value" << std::endl << std::flush;
}

void
CsvCollector::PrintDoubleProbe (std::string context, Time time, double val)
{
  ProbeMap::iterator probe = m_probes.find (context);
  NS_ASSERT (probe != m_probes.end ());
  ProbeDescriptor* desc = probe->second;
  desc->m_of << time.GetSeconds () << "," << val << std::endl << std::flush;  
}

void
CsvCollector::AddStringProbe (Ptr<StringProbe> p, std::string probeName)
{
  NS_ASSERT (m_probes.find (probeName) == m_probes.end());
  p->TraceConnect ("Output", probeName, MakeCallback (&CsvCollector::PrintStringProbe , this));
  ProbeDescriptor*  desc  = new ProbeDescriptor (p, probeName + ".csv");
  m_probes.insert (std::make_pair (probeName, desc));
  desc->m_of << "time,value" << std::endl << std::flush;
}

void
CsvCollector::PrintStringProbe (std::string context, Time time, std::string const & val)
{
  ProbeMap::iterator probe = m_probes.find (context);
  NS_ASSERT (probe != m_probes.end ());
  ProbeDescriptor* desc = probe->second;
  desc->m_of << time.GetSeconds () << "," << val << std::endl << std::flush;  
}


}
