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

#ifndef DCF_HELPER_H
#define DCF_HELPER_H

#include "ns3/object.h"
#include "ns3/log.h"
#include "experiment.h"


//
// helper creates collectors and experiments
//
// it should contain an experiment
// it should contain a list of all and/or collectors
//

namespace ns3 {

		class DcfHelper : public Object {
			public:
				static TypeId GetTypeId (void);

				DcfHelper ();
				virtual ~DcfHelper ();

				
			private:
				// experiment ids must be globally unique
				static std::string m_experimentId;
				static std::string m_runId;
				static std::string m_expDescription;

		} // class DcfHelper

} // namespace ns3



#endif // DCF_HELPER_H
