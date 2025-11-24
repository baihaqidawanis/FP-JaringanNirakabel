/*
 * =================================================================================
 * TUGAS BESAR JARINGAN NIRKABEL - IMPLEMENTASI AODV TRUST
 * =================================================================================
 * Judul Topik : Pengembangan Protokol AODV-Trust untuk Meningkatkan Keandalan 
 * Routing pada Jaringan MANET
 *
 * Disusun Oleh:
 * 1. Muhammad Baihaqi Dawanis (5025231177)
 * 2. Abimanyu Dananedra Andarfebano (5025231182)
 *
 * Deskripsi Script:
 * Script ini mensimulasikan jaringan MANET dengan 25 Node menggunakan model
 * mobilitas Random Waypoint. Script ini dirancang untuk mendemonstrasikan
 * perbedaan kinerja antara AODV Standard (Insecure) dan AODV-Trust (Secure).
 *
 * Skenario Pengujian:
 * - Jumlah Node: 25 Node
 * - Area: 100x100 meter
 * - Durasi: 20 Detik
 * - Trafik: UDP Echo (CBR)
 * - Output: Animasi NetAnim (.xml) & Statistik PDR/Throughput
 * =================================================================================
 */

#include "ns3/aodv-trust-helper.h" 
#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/internet-module.h"
#include "ns3/mobility-module.h"
#include "ns3/applications-module.h"
#include "ns3/wifi-module.h"
#include "ns3/netanim-module.h"    
#include "ns3/flow-monitor-module.h"

using namespace ns3;
using namespace ns3::aodv_trust; // Menggunakan namespace protokol kita

NS_LOG_COMPONENT_DEFINE("AodvTrustManetExample");

int main(int argc, char *argv[])
{
    // 1. Parameter Default
    uint32_t nNodes = 25;          
    double totalTime = 20.0;       
    bool useTrustProtocol = true;  // Default: Pakai Trust (Secure)

    // 2. Parsing Command Line (Supaya bisa diatur lewat terminal)
    CommandLine cmd(__FILE__);
    cmd.AddValue("nNodes", "Number of nodes", nNodes);
    // INI YANG TADI HILANG:
    cmd.AddValue("useTrust", "Enable Trust Mechanism (true=AODV-Trust, false=AODV-Std)", useTrustProtocol);
    cmd.Parse(argc, argv);

    // 3. Setting Saklar Protokol (Mengirim nilai ke AodvTrustRoutingProtocol)
    // Jika useTrust = false, protokol akan mematikan fitur trust (jadi AODV biasa)
    Config::SetDefault("ns3::aodv_trust::AodvTrustRoutingProtocol::EnableTrust", BooleanValue(useTrustProtocol));
    
    // Print Status Mode ke Terminal
    if (useTrustProtocol) {
        NS_LOG_UNCOND("===============================================");
        NS_LOG_UNCOND(">>> RUNNING MODE: AODV-TRUST (SECURE)       <<<");
        NS_LOG_UNCOND(">>> Mekanisme filtering node jahat: AKTIF   <<<");
        NS_LOG_UNCOND("===============================================");
    } else {
        NS_LOG_UNCOND("===============================================");
        NS_LOG_UNCOND(">>> RUNNING MODE: AODV STANDARD (INSECURE)  <<<");
        NS_LOG_UNCOND(">>> Mekanisme filtering node jahat: MATI    <<<");
        NS_LOG_UNCOND("===============================================");
    }

    // 4. Membuat Node
    NodeContainer nodes;
    nodes.Create(nNodes);

    // 5. Setup Wifi
    WifiHelper wifi;
    wifi.SetStandard(WIFI_STANDARD_80211b);

    YansWifiPhyHelper wifiPhy;
    YansWifiChannelHelper wifiChannel = YansWifiChannelHelper::Default();
    wifiPhy.SetChannel(wifiChannel.Create());

    WifiMacHelper wifiMac;
    wifiMac.SetType("ns3::AdhocWifiMac");

    NetDeviceContainer devices;
    devices = wifi.Install(wifiPhy, wifiMac, nodes);

    // 6. Setup Mobilitas
    MobilityHelper mobility;
    mobility.SetPositionAllocator("ns3::GridPositionAllocator",
                                  "MinX", DoubleValue(0.0), "MinY", DoubleValue(0.0),
                                  "DeltaX", DoubleValue(20.0), "DeltaY", DoubleValue(20.0),
                                  "GridWidth", UintegerValue(5), "LayoutType", StringValue("RowFirst"));
    
    // Objek RandomAllocator (Penting supaya tidak error Assert)
    ObjectFactory posAlg;
    posAlg.SetTypeId("ns3::RandomRectanglePositionAllocator");
    posAlg.Set("X", StringValue("ns3::UniformRandomVariable[Min=0.0|Max=100.0]"));
    posAlg.Set("Y", StringValue("ns3::UniformRandomVariable[Min=0.0|Max=100.0]"));
    Ptr<PositionAllocator> taPositionAlloc = posAlg.Create<PositionAllocator>();

    mobility.SetMobilityModel("ns3::RandomWaypointMobilityModel",
                              "Speed", StringValue("ns3::UniformRandomVariable[Min=1.0|Max=10.0]"),
                              "Pause", StringValue("ns3::ConstantRandomVariable[Constant=2.0]"),
                              "PositionAllocator", PointerValue(taPositionAlloc));
                              
    mobility.Install(nodes);
    mobility.AssignStreams(nodes, 0);

    // 7. Install Protokol Routing
    InternetStackHelper stack;
    AodvTrustHelper aodvTrust; 
    stack.SetRoutingHelper(aodvTrust); // Selalu pakai helper kita
    stack.Install(nodes);

    // 8. Assign IP
    Ipv4AddressHelper address;
    address.SetBase("10.1.1.0", "255.255.255.0");
    Ipv4InterfaceContainer interfaces = address.Assign(devices);

    // 9. Setup Aplikasi (Trafik)
    uint16_t port = 9;
    // Penerima (Node Terakhir)
    UdpEchoServerHelper server(port);
    ApplicationContainer apps = server.Install(nodes.Get(nNodes - 1));
    apps.Start(Seconds(1.0));
    apps.Stop(Seconds(totalTime));

    // Pengirim (Node Pertama)
    UdpEchoClientHelper client(interfaces.GetAddress(nNodes - 1), port);
    client.SetAttribute("MaxPackets", UintegerValue(100));
    client.SetAttribute("Interval", TimeValue(Seconds(0.5))); 
    client.SetAttribute("PacketSize", UintegerValue(1024));

    apps = client.Install(nodes.Get(0));
    apps.Start(Seconds(2.0));
    apps.Stop(Seconds(totalTime));

    // 10. Visualisasi NetAnim
    // Nama file animasi beda tergantung mode, biar ga ketimpa
    std::string animFile = useTrustProtocol ? "anim-trust.xml" : "anim-std.xml";
    AnimationInterface anim(animFile);
    anim.EnablePacketMetadata(true); 
    anim.UpdateNodeColor(nodes.Get(0), 0, 255, 0); // Hijau (Pengirim)
    anim.UpdateNodeColor(nodes.Get(nNodes - 1), 255, 0, 0); // Merah (Penerima)

    // 11. Flow Monitor
    FlowMonitorHelper flowmon;
    Ptr<FlowMonitor> monitor = flowmon.InstallAll();

    NS_LOG_UNCOND("Starting Simulation...");
    Simulator::Stop(Seconds(totalTime));
    Simulator::Run();

    // 12. Cetak Hasil
    monitor->CheckForLostPackets();
    Ptr<Ipv4FlowClassifier> classifier = DynamicCast<Ipv4FlowClassifier>(flowmon.GetClassifier());
    std::map<FlowId, FlowMonitor::FlowStats> stats = monitor->GetFlowStats();

    for (std::map<FlowId, FlowMonitor::FlowStats>::const_iterator i = stats.begin(); i != stats.end(); ++i)
    {
        Ipv4FlowClassifier::FiveTuple t = classifier->FindFlow(i->first);
        if (t.sourceAddress == "10.1.1.1") 
        {
             NS_LOG_UNCOND("------------------------------------------------");
             NS_LOG_UNCOND("Flow ID    : " << i->first);
             NS_LOG_UNCOND("Src -> Dst : " << t.sourceAddress << " -> " << t.destinationAddress);
             NS_LOG_UNCOND("Tx Packets : " << i->second.txPackets);
             NS_LOG_UNCOND("Rx Packets : " << i->second.rxPackets);
             
             double pdr = 0;
             if (i->second.txPackets > 0) {
                 pdr = ((double)i->second.rxPackets / i->second.txPackets) * 100;
             }
             NS_LOG_UNCOND("PDR        : " << pdr << " %");
             NS_LOG_UNCOND("Throughput : " << i->second.rxBytes * 8.0 / (totalTime * 1000000.0) << " Mbps");
             NS_LOG_UNCOND("------------------------------------------------");
        }
    }

    Simulator::Destroy();
    return 0;
}