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
#include "ns3/log.h"
#include "ns3/boolean.h"

#include "probe-helper.h"

//NS_LOG_COMPONENT_DEFINE("ProbeHelper");

namespace ns3 {

NS_OBJECT_ENSURE_REGISTERED (ProbeHelper);

ProbeHelper::ProbeHelper() 
{
}

ProbeHelper::~ProbeHelper()
{
}

TypeId
ProbeHelper::GetTypeId (void)
{
  static TypeId tid = TypeId ("ns3::ProbeHelper")
    .SetParent<Object> ()
    .AddAttribute ("ProbeGlobalEnable", 
          "whether all probes are enabled",
          BooleanValue (true),
          MakeBooleanAccessor(&ProbeHelper::GetProbeGlobalStatus,
            &ProbeHelper::SetProbeGlobalStatus),
          MakeBooleanChecker())
    ;
  return tid;
}

bool ProbeHelper::GetProbeGlobalStatus () const
{
  return true;
}

void ProbeHelper::SetProbeGlobalStatus (bool enable)
{

}

} // namespace ns3
