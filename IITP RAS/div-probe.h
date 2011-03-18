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
#include "ns3/simulator.h"
#include "ns3/traced-callback.h"
#include <string>

namespace ns3 {

/**
 * \brief Probe to divide 2 syncronous time series
 */
class DivProbe : public DoubleProbe
{
public:
  static TypeId GetTypeId ();
  DivProbe ();
  virtual ~DivProbe () {}

  /// Set input trace sources. Both nominator and denominator trace sources must have signature (Time, double) and must fire simultaneously.
  void SetInput (std::string nominator, std::string denominator);

private:
  std::string m_nominatorName;
  std::string m_denominatorName;
  double m_lastNom, m_lastDenom;
  bool m_lastNomUpd, m_lastDenomUpd;
  Time m_lastNomTs, m_lastDenomTs;

private:
  void ConnectInput ();
  void Report ();
  void StopProbe ();
  void ProcessNominator (Time t, double val);
  void ProcessDenominator (Time t, double val);
};

}
