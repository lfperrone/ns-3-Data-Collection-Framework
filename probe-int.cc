/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2010 Bucknell University
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

#include "ns3/object.h"
#include "ns3/traced-value.h"
#include "ns3/log.h"

#include "probe-int.h"

NS_LOG_COMPONENT_DEFINE("ProbeInt");

namespace ns3 {

NS_OBJECT_ENSURE_REGISTERED (ProbeInt);

TypeId 
ProbeInt::GetTypeId (void) 
{
  NS_LOG_FUNCTION_NOARGS();

  static TypeId tid = TypeId ("ns3::ProbeInt")
    .SetParent<Probe> ()
    .AddConstructor<ProbeInt> ()
    .AddAttribute("ProbeInt status",
        "whether the probe is enabled or not",
        BooleanValue (true),
        MakeBooleanAccessor (&ProbeInt::GetProbeStatus,
          &ProbeInt::SetProbeStatus),
        MakeBooleanChecker())
    ;
  return tid;

} // ProbeInt::GetTypeId

ProbeInt::ProbeInt () 
{
	NS_LOG_FUNCTION_NOARGS();
} // ProbeInt::ProbeInt()

ProbeInt::~ProbeInt () 
{
	NS_LOG_FUNCTION(this);
} // ProbeInt::~ProbeInt()

bool ProbeInt::GetProbeStatus (void) const
{
  return true;
}

void ProbeInt::SetProbeStatus (bool enabled)
{
}

} // namespace ns3

