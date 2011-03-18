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

#include "div-probe.h"
#include "ns3/config.h"
#include "ns3/log.h"

namespace ns3 {

NS_LOG_COMPONENT_DEFINE ("DivProbe");
NS_OBJECT_ENSURE_REGISTERED (DivProbe);

TypeId 
DivProbe::GetTypeId ()
{
  static TypeId tid = TypeId ("ns3::DivProbe")
    .SetParent<DoubleProbe> ()
    .AddConstructor<DivProbe> ()
    ;
  return tid;
}

DivProbe::DivProbe ()
  :
    m_lastNom (0),
    m_lastDenom (0),
    m_lastNomUpd (false),
    m_lastDenomUpd (false),
    m_lastNomTs (Seconds (0)),
    m_lastDenomTs (Seconds(0))
{
}

void
DivProbe::StopProbe ()
{
  NS_LOG_FUNCTION_NOARGS ();
  Config::DisconnectWithoutContext (m_nominatorName, MakeCallback (&DivProbe::ProcessNominator, this));
  Config::DisconnectWithoutContext (m_denominatorName, MakeCallback (&DivProbe::ProcessDenominator, this));
}

void
DivProbe::SetInput (std::string nominator, std::string denominator)
{
  NS_LOG_FUNCTION_NOARGS ();

  m_nominatorName = nominator;
  m_denominatorName = denominator;

  Simulator::Schedule (m_start, &DivProbe::ConnectInput, this);
  Simulator::Schedule (m_stop, &DivProbe::StopProbe, this);
}

void
DivProbe::ConnectInput ()
{
  NS_LOG_FUNCTION_NOARGS ();

  Config::ConnectWithoutContext (m_nominatorName, MakeCallback (& DivProbe::ProcessNominator, this));
  Config::ConnectWithoutContext (m_denominatorName, MakeCallback (& DivProbe::ProcessDenominator, this));
}

void
DivProbe::ProcessNominator (Time t, double val)
{
  NS_LOG_FUNCTION (t);
  m_lastNom = val;
  m_lastNomUpd = true;
  m_lastNomTs = t;
  Report ();
}

void
DivProbe::ProcessDenominator (Time t, double val)
{
  NS_LOG_FUNCTION (t);
  m_lastDenom = val;
  m_lastDenomUpd = true;
  m_lastDenomTs = t;
  Report ();
}

void
DivProbe::Report ()
{
  if (m_lastNomUpd != m_lastDenomUpd) return;

  NS_ASSERT_MSG (m_lastDenomTs == m_lastNomTs, "Nominator and denominator time series are not synchronous.");
  Output (m_lastDenomTs, m_lastNom / m_lastDenom);
  m_lastNomUpd = m_lastDenomUpd = false;
}
}//namespace ns3
