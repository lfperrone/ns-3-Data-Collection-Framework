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

#include "ns3/log.h"
#include "probe-factory.h"

NS_LOG_COMPONENT_DEFINE("ProbeFactory");

namespace ns3 {

NS_OBJECT_ENSURE_REGISTERED (ProbeFactory);

TypeId 
ProbeFactory::GetTypeId (void) 
{
  NS_LOG_FUNCTION_NOARGS();

  static TypeId tid = TypeId ("ns3::ProbeFactory")
    .SetParent<Object> ();
  return tid;

} // ProbeFactory::GetTypeId

ProbeFactory::ProbeFactory () 
{
	NS_LOG_FUNCTION_NOARGS();
} // ProbeFactory::ProbeFactory()

} // namespace ns3

