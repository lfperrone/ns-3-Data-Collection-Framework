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
#include "ns3/traced-source-accessor.h"
#include "ns3/log.h"

#include "collector-sample.h"

NS_LOG_COMPONENT_DEFINE("CollectorSample");

namespace ns3 {

NS_OBJECT_ENSURE_REGISTERED (CollectorSample);

TypeId 
CollectorSample::GetTypeId (void) 
{
  NS_LOG_FUNCTION_NOARGS();

  static TypeId tid = TypeId ("ns3::CollectorSample")
    .SetParent<Object> ()
    .AddConstructor<CollectorSample> ()
    .AddTraceSource ("MyValue",
        "A value collected by a collector",
        MakeTraceSourceAccessor(&CollectorSample::m_value);
    ;
  return tid;
}

CollectorSample::CollectorSample () 
{
	NS_LOG_FUNCTION_NOARGS();
}

CollectorSample::~CollectorSample () 
{
	NS_LOG_FUNCTION_NOARGS();
}

double
CollectorSample::GetMean() 
{
  return m_mean;
}

double
CollectorSample::GetVariance()
{
  return m_var;
}

double
CollectorSample::GetStDev()
{
  return sqrt(m_var);
}

double
CollectorSample::GetSum()
{
  return m_sum;
}

double
CollectorSample::GetMax()
{
  return m_MaxValue;
}

double
CollectorSample::GetMin()
{
  return m_MinValue;
}

unsigned long
CollectorSample::GetNumSamples()
{
  return m_samples.size();
}

void 
CollectorSample::AddSample(double s) 
{
  double delta = s - m_mean;
  double old_mean = m_mean;

  m_samples.push_back(s);

  // update recorded min and max values
  if (m_samples.size() == 1) {
    m_minValue = m_maxValue = s;
    m_sum = s;
    m_sumsqr = s * s;
  } else {
    if (s > m_maxValue)
      m_maxValue = s;
    else if (s < minValue) 
      m_minValue = s;
  }

  // update mean and var via Welford's one pass algorithm
  m_mean += (delta/m_samples.size());
  m_sum += s;
  m_sumsqr += (delta * delta) * (m_samples.size() - 1) / m_samples.size(); 
  m_var = m_sumsqr / m_samples.size();
}

double
CollectorSample::WindowAverage(int wpos, int wsize)
{
  double wsum = 0;

  for (int i=0; i < wsize; i++)
    wsum += m_samples[wpos+i];

  return wsum/wsize;
}

vector<double> *
CollectorSample::MovingAverages(int wsize)
{
  vector<double> *avgs = new vector<double>;

  for (int i=0; i < (m_samples.size() - wsize); i++) {
    (*avgs)[i] = WindowAverage(i, wsize);
  }

  return avgs;
}


} // namespace ns3

