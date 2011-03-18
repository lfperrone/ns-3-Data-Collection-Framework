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

#include "ns3/object.h"
#include "ns3/nstime.h"

namespace ns3 {

/**
 * \brief Base class for all probes
 * 
 * The base class provides general data collection setup, to be used as:
 * 
 * Config::SetDefault ("ns3::Probe::Start", TimeValue (Seconds(0)));
 * Config::SetDefault ("ns3::Probe::Stop",  TimeValue (Seconds (100)));
 * Config::SetDefault ("ns3::Probe::Period",  TimeValue (Seconds(5)));
 *
 * Note that nothing prevents derived classes from neglecting these. 
 */
class Probe : public Object
{
public:
  static TypeId GetTypeId ();
  Probe ();
  virtual ~Probe ();

protected:
  /// Start and stop times, periodicity
  Time m_start, m_stop, m_period;
};

}
