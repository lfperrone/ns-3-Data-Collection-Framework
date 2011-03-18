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

#ifndef COLLECTOR_SAMPLE_H
#define COLLECTOR_SAMPLE_H

#include "ns3/object.h"
#include <vector>

namespace ns3 {	

	class CollectorSample : public DataCollection {
	public:
		static TypeId GetTypeId ();

		CollectorSample ();
		virtual ~CollectorSample ();

		/// Computes current sample mean (Welford's one pass algorithm)
		double GetMean();

		/// Computes current sample variance (Welford's one pass algorithm)
		double GetVariance();
    
		/// Number of samples stored
		unsigned long GetNumSamples();

		/// Summation of all stored samples
		double GetSum();

		/// Largest sample value stored
    double GetMax();

		/// Smallest sample value stored
		double GetMin();

		/// Window average
		double WindowAverage(int wpos, int wsize);
		
		vector<double> WindowAverages(int wsize);
	private:
		vector<double> m_samples;
		double m_minValue;
		double m_maxValue;
		double m_sum;
		double m_sumsqr;
		double m_mean;
		double m_var;
	
	}; // class CollectorSample

} // namespace ns3

#endif // COLLECTOR_SAMPLE_H
