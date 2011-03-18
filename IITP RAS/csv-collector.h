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
#pragma once

#include "double-probe.h"
#include "string-probe.h"
#include "ns3/object.h"
#include "ns3/nstime.h"
#include "ns3/traced-callback.h"
#include <string>
#include <fstream>

#include <map>

namespace ns3 {

/**
 * \brief CSV collector stores every supported probe as {time, value} series in the dedicated CSV file
 *
 * Supported probes:
 *  - DoubleProbe
 * 
 * This is proof of concept implementation, many useful features can be supported in the future.
 */
class CsvCollector : public Object
{
public:
  static TypeId GetTypeId ();
  CsvCollector ();
  ~CsvCollector ();

  /**
   * Register new double probe
   *
   * \param p         The probe
   * \param probeName Probe name, should be unique in the context of this collector
   */
  void AddDoubleProbe (Ptr<DoubleProbe> p, std::string name);
  /// Register new string probe
  void AddStringProbe (Ptr<StringProbe> p, std::string name);

private:
  /// Internal probe description
  struct ProbeDescriptor
  {
    Ptr<Probe> m_probe;
    std::ofstream m_of;
    ProbeDescriptor (Ptr<Probe> probe, std::string name);
    ~ProbeDescriptor ();
  };

private:
  typedef std::map<std::string, ProbeDescriptor* > ProbeMap;
  ProbeMap m_probes;

private:
  void PrintDoubleProbe (std::string context, Time time, double val);
  void PrintStringProbe (std::string context, Time time, std::string const & val);
};

}
