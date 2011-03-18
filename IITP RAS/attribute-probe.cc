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

#include "attribute-probe.h"
#include "ns3/simulator.h"
#include "ns3/string.h"

namespace ns3 {

NS_OBJECT_ENSURE_REGISTERED (AttributeProbe);

TypeId 
AttributeProbe::GetTypeId ()
{
  static TypeId tid = TypeId ("ns3::AttributeProbe")
    .SetParent<StringProbe> ()
    .AddConstructor<AttributeProbe> ()
    ;
  return tid;
}

AttributeProbe::~AttributeProbe ()
{
}

void
AttributeProbe::SetInput (Ptr<Object> obj, std::string const & path)
{
  NS_ASSERT (obj != 0);
  Simulator::Schedule (m_stop, & AttributeProbe::Report, this, obj, path);  
}

void
AttributeProbe::Report (Ptr<Object> obj, std::string const & path)
{
  StringValue str;
  obj->GetAttribute (path, str);
  Output (Simulator::Now(), str.SerializeToString (0));
}

}
