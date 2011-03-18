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
#include "ns3/event-id.h"
#include "ns3/packet.h"
#include <string>

namespace ns3 {

/**
 * \brief This probes counts the total number of input events
 */
class CountProbe : public DoubleProbe
{
public:
  static TypeId GetTypeId ();
  CountProbe () {}
  ~CountProbe () {}

  //\name Set input trace source. Path is a connect string, e.g. "Names/obj/Trace". The variety of Set*Input methods is needed to count events with different signatures.
  //\{
  /// Input trace source signature is (void)
  void SetVoidInput (std::string path);
  /// Input trace source signature is (Ptr<const Packet>)
  void SetPacketInput (std::string path);
  //\}

private:
  /// Input path
  std::string m_name;
  /// Counter value
  double m_count;
  /// Next report event
  EventId m_reportEvent;

private:
  void ConnectVoid (); 
  void DisconnectVoid ();
  void Count ();

  void ConnectPacket ();
  void DisconnectPacket ();
  void CountPackets (Ptr<const Packet> packet);

  void Report ();
  void StopProbe ();
};

}
