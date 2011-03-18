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

#include "string-probe.h"
#include "ns3/traced-callback.h"
#include "ns3/object.h"

namespace ns3 {

/**
 * \brief Probe returning attribute value at the end of data collection window (as {time, string})
 */
class AttributeProbe : public StringProbe
{
public:
  static TypeId GetTypeId ();
  virtual ~AttributeProbe ();

  /// Set probed attribute
  void SetInput (Ptr<Object> obj, std::string const & attribute);

private:
  void Report (Ptr<Object> obj, std::string const & path);
};

}//namespace ns3
