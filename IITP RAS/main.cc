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

#include "csv-collector.h"
#include "count-probe.h"
#include "div-probe.h"
#include "attribute-probe.h"

#include "ns3/olsr-module.h"
#include "ns3/core-module.h"
#include "ns3/common-module.h"
#include "ns3/node-module.h"
#include "ns3/helper-module.h"
#include "ns3/mobility-module.h"
#include "ns3/contrib-module.h"
#include "ns3/wifi-module.h" 
#include "ns3/v4ping-helper.h"
#include <iostream>
#include <cmath>

using namespace ns3;

/**
 * \brief Test script.
 * 
 * This script creates 1-dimensional grid topology and then ping last node from the first one:
 * 
 * [10.0.0.1] <-- step --> [10.0.0.2]
 * 
 * ping 10.0.0.2
 */
class Example 
{
public:
  Example ();
  /// Configure script parameters, \return true on successful configuration
  bool Configure (int argc, char **argv);
  /// Run simulation
  void Run ();
  /// Report results
  void Report (std::ostream & os);
  
private:
  ///\name parameters
  //\{
  /// Number of nodes
  uint32_t size;
  /// Distance between nodes, meters
  double step;
  /// Simulation time, seconds
  double totalTime;
  //\}
  
  ///\name network
  //\{
  NodeContainer nodes;
  NetDeviceContainer devices;
  Ipv4InterfaceContainer interfaces;
  //\}
  

  /// Data collector
  Ptr<CsvCollector> collector;

private:
  void CreateNodes ();
  void CreateDevices ();
  void InstallInternetStack ();
  void InstallApplications ();
  
  void SetupDataCollection (); ///<============================================= The most interesting part here ===|
};

int main (int argc, char **argv)
{
  Example test;
  if (! test.Configure(argc, argv)) 
    NS_FATAL_ERROR ("Configuration failed. Aborted.");
  
  test.Run ();
  test.Report (std::cout);
  return 0;
}

//-----------------------------------------------------------------------------
Example::Example () :
  size (2),
  step (120),
  totalTime (10)
{
}

bool
Example::Configure (int argc, char **argv)
{
  CommandLine cmd;
  
  cmd.AddValue ("time", "Simulation time, s.", totalTime);
  
  cmd.Parse (argc, argv);
  return true;
}

void
Example::Run ()
{
  CreateNodes ();
  CreateDevices ();
  InstallInternetStack ();
  InstallApplications ();
  
  SetupDataCollection ();

  
  std::cout << "Starting simulation for " << totalTime << " s ...\n";
  
  Simulator::Stop (Seconds (totalTime));
  Simulator::Run ();
  Simulator::Destroy ();
}

void
Example::Report (std::ostream &)
{ 
}

void
Example::CreateNodes ()
{
  std::cout << "Creating " << (unsigned)size << " nodes " << step << " m apart.\n";
  nodes.Create (size);
  // Name nodes
  for (uint32_t i = 0; i < size; ++i)
     {
       std::ostringstream os;
       os << "node-" << i;
       Names::Add (os.str (), nodes.Get (i));
     }
  // Create static grid
  MobilityHelper mobility;
  mobility.SetPositionAllocator ("ns3::GridPositionAllocator",
                                "MinX", DoubleValue (0.0),
                                "MinY", DoubleValue (0.0),
                                "DeltaX", DoubleValue (step),
                                "DeltaY", DoubleValue (0),
                                "GridWidth", UintegerValue (size),
                                "LayoutType", StringValue ("RowFirst"));
  mobility.SetMobilityModel ("ns3::ConstantPositionMobilityModel");
  mobility.Install (nodes);
}

void
Example::CreateDevices ()
{
  NqosWifiMacHelper wifiMac = NqosWifiMacHelper::Default ();
  wifiMac.SetType ("ns3::AdhocWifiMac");
  YansWifiPhyHelper wifiPhy = YansWifiPhyHelper::Default ();
  YansWifiChannelHelper wifiChannel = YansWifiChannelHelper::Default ();
  wifiPhy.SetChannel (wifiChannel.Create ());
  WifiHelper wifi = WifiHelper::Default ();
  wifi.SetRemoteStationManager ("ns3::ConstantRateWifiManager", "DataMode", StringValue ("OfdmRate6Mbps"));
  devices = wifi.Install (wifiPhy, wifiMac, nodes); 
  wifiPhy.EnablePcapAll (std::string ("olsr"));
}

void
Example::InstallInternetStack ()
{
  OlsrHelper olsr;
  InternetStackHelper stack;
  stack.SetRoutingHelper (olsr);
  stack.Install (nodes);
  Ipv4AddressHelper address;
  address.SetBase ("10.0.0.0", "255.0.0.0");
  interfaces = address.Assign (devices);
}

void
Example::InstallApplications ()
{
  V4PingHelper ping (interfaces.GetAddress (size - 1));
  ping.SetAttribute ("Verbose", BooleanValue (true));
  
  ApplicationContainer p = ping.Install (nodes.Get (0));
  p.Start (Seconds (0));
  p.Stop (Seconds (totalTime));

  Names::Add ("ping", p.Get(0)); // Name application to simplify data collection setup
}

void 
Example::SetupDataCollection ()
{
  // Setup data collection window and periodicity
  Config::SetDefault ("ns3::Probe::Start", TimeValue (Seconds(0)));
  Config::SetDefault ("ns3::Probe::Stop",  TimeValue (Seconds (totalTime)));
  Config::SetDefault ("ns3::Probe::Period",  TimeValue (Seconds(2)));
  
  // Count TX and RX packets
  collector = CreateObject<CsvCollector> ();
  
  // Count transmitted echo requests
  Ptr<CountProbe> p1 = CreateObject<CountProbe> ();
  p1->SetVoidInput ("Names/ping/Tx");
  Names::Add ("PingTxProbe", p1);
  collector->AddDoubleProbe(p1, "ping-tx");

  // Count received echo replies
  Ptr<CountProbe> p2 = CreateObject<CountProbe> ();
  p2->SetVoidInput ("Names/ping/Rx");
  Names::Add ("PingRxProbe", p2);  
  collector->AddDoubleProbe(p2, "ping-rx");
  
  // Total number of packets sent 
  // This is an example of "global" probe, note "*" in the input path
  Ptr<CountProbe> p3 = CreateObject<CountProbe> ();
  p3->SetPacketInput("NodeList/*/DeviceList/*/$ns3::WifiNetDevice/Mac/MacTx");
  collector->AddDoubleProbe(p3, "wifi-tx");
    
  // Calculate PDR
  // This is an example of probe tree
  Ptr<DivProbe> p4 = CreateObject<DivProbe> ();
  p4->SetInput ("Names/PingRxProbe/Output", "Names/PingTxProbe/Output");
  collector->AddDoubleProbe (p4, "ping-pdr");

  // Store ping payload size to the output database   
  // Note that current API is not-uniform, better written as p5->SetInput("Names/ping/Size"), but I don't know how to implement
  Ptr<AttributeProbe> p5 = CreateObject<AttributeProbe> ();
  p5->SetInput (Names::Find<Object> ("ping"), "Size");      
  collector->AddStringProbe (p5, "ping-size");
}
