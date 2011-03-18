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

#include "probe.h"

namespace ns3 {

NS_OBJECT_ENSURE_REGISTERED (Probe);

TypeId 
Probe::GetTypeId ()
{
  static TypeId tid = TypeId ("ns3::Probe")
    .SetParent<Object> ()
    .AddConstructor<Probe> ()
    .AddAttribute ( "Start",
                    "A moment when a probe starts collecting data",
                    TimeValue (Seconds (0)), MakeTimeAccessor (&Probe::m_start), MakeTimeChecker ())
    .AddAttribute ( "Stop",
                    "A moment when a probe stops collecting data",
                    TimeValue (Seconds (1)), MakeTimeAccessor (&Probe::m_stop), MakeTimeChecker ())
    .AddAttribute ( "Period",
                    "Time step for periodic probes",
                    TimeValue (Seconds (1)), MakeTimeAccessor (&Probe::m_period), MakeTimeChecker ())
  ;
  return tid;
}

Probe::Probe () :
  m_start (Seconds(0)),
  m_stop (Seconds (1)),
  m_period (Seconds (1))
{
}

Probe::~Probe ()
{
}

}//namespace ns3
