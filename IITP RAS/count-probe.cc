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

#include "count-probe.h"
#include "ns3/trace-source-accessor.h"
#include "ns3/simulator.h"
#include "ns3/config.h"
#include "ns3/log.h"

namespace ns3 {

NS_LOG_COMPONENT_DEFINE ("CountProbe");
NS_OBJECT_ENSURE_REGISTERED (CountProbe);

TypeId 
CountProbe::GetTypeId ()
{
  static TypeId tid = TypeId ("ns3::CountProbe")
    .SetParent<DoubleProbe> ()
    .AddConstructor<CountProbe> ()
    ;
  return tid;
}

void
CountProbe::SetVoidInput (std::string path)
{
  NS_LOG_FUNCTION (path);
  m_name = path;
  Simulator::Schedule (m_start, &CountProbe::ConnectVoid, this);
  Simulator::Schedule (m_stop, &CountProbe::DisconnectVoid, this);
}

void
CountProbe::SetPacketInput (std::string path)
{  
  NS_LOG_FUNCTION (path);
  m_name = path;
  Simulator::Schedule (m_start, &CountProbe::ConnectPacket, this);
  Simulator::Schedule (m_stop, &CountProbe::DisconnectPacket, this);
}

void
CountProbe::ConnectVoid ()
{
  NS_LOG_FUNCTION_NOARGS ();
  NS_ASSERT (m_period > Seconds (0));
  NS_ASSERT (m_stop > m_start);
  Config::ConnectWithoutContext (m_name, MakeCallback (& CountProbe::Count, this));
  m_reportEvent = Simulator::Schedule (m_period, &CountProbe::Report, this);
}

void
CountProbe::ConnectPacket ()
{
  NS_LOG_FUNCTION_NOARGS ();
  NS_ASSERT (m_period > Seconds (0));
  NS_ASSERT (m_stop > m_start);
  Config::ConnectWithoutContext (m_name, MakeCallback (& CountProbe::CountPackets, this));
  m_reportEvent = Simulator::Schedule (m_period, &CountProbe::Report, this);
}

void
CountProbe::Report ()
{
  NS_LOG_FUNCTION_NOARGS ();
  NS_ASSERT (! m_reportEvent.IsRunning ());
  Output (Simulator::Now (), m_count);
  m_count = 0;
  m_reportEvent = Simulator::Schedule (m_period, &CountProbe::Report, this);
}

void
CountProbe::DisconnectPacket ()
{
  Config::DisconnectWithoutContext (m_name, MakeCallback (&CountProbe::CountPackets, this));
  StopProbe ();
}

void
CountProbe::DisconnectVoid ()
{
  Config::DisconnectWithoutContext (m_name, MakeCallback (&CountProbe::Count, this));
  StopProbe ();
}

void
CountProbe::StopProbe ()
{
  NS_LOG_FUNCTION_NOARGS();
  m_reportEvent.Cancel ();
  Output (Simulator::Now (), m_count);
}

void
CountProbe::Count ()
{
  NS_LOG_FUNCTION_NOARGS ();
  m_count ++;
}

void
CountProbe::CountPackets (Ptr<const Packet>)
{
  Count ();
}
}//namespace ns3
