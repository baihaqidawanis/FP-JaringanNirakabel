/* --- MODIFIKASI AODV-TRUST: Helper Source (FIXED NAMESPACE) --- */
#include "aodv-trust-helper.h"
#include "ns3/aodv-trust-routing-protocol.h"
#include "ns3/node-list.h"
#include "ns3/names.h"
#include "ns3/ptr.h"
#include "ns3/ipv4-list-routing.h"

namespace ns3
{

AodvTrustHelper::AodvTrustHelper()
{
    // Menggunakan TypeId namespace yang benar: aodv_trust
    m_agentFactory.SetTypeId("ns3::aodv_trust::AodvTrustRoutingProtocol");
}

AodvTrustHelper*
AodvTrustHelper::Copy() const
{
    return new AodvTrustHelper(*this);
}

Ptr<Ipv4RoutingProtocol>
AodvTrustHelper::Create(Ptr<Node> node) const
{
    // FIX: Menggunakan namespace aodv_trust
    Ptr<aodv_trust::AodvTrustRoutingProtocol> agent = m_agentFactory.Create<aodv_trust::AodvTrustRoutingProtocol>();
    node->AggregateObject(agent);
    return agent;
}

void
AodvTrustHelper::Set(std::string name, const AttributeValue& value)
{
    m_agentFactory.Set(name, value);
}

int64_t
AodvTrustHelper::AssignStreams(NodeContainer c, int64_t stream)
{
    int64_t currentStream = stream;
    Ptr<Node> node;
    for (NodeContainer::Iterator i = c.Begin(); i != c.End(); ++i)
    {
        node = (*i);
        Ptr<Ipv4> ipv4 = node->GetObject<Ipv4>();
        NS_ASSERT_MSG(ipv4, "Ipv4 not installed on node");
        Ptr<Ipv4RoutingProtocol> proto = ipv4->GetRoutingProtocol();
        NS_ASSERT_MSG(proto, "Ipv4 routing not installed on node");
        
        // FIX: Menggunakan namespace aodv_trust
        Ptr<aodv_trust::AodvTrustRoutingProtocol> aodv = DynamicCast<aodv_trust::AodvTrustRoutingProtocol>(proto);
        if (aodv)
        {
            currentStream += aodv->AssignStreams(currentStream);
            continue;
        }
        // Aodv may also be in a list
        Ptr<Ipv4ListRouting> list = DynamicCast<Ipv4ListRouting>(proto);
        if (list)
        {
            int16_t priority;
            Ptr<Ipv4RoutingProtocol> listProto;
            // Check if aodv is in list
            for (uint32_t i = 0; i < list->GetNRoutingProtocols(); i++)
            {
                listProto = list->GetRoutingProtocol(i, priority);
                // FIX: Menggunakan namespace aodv_trust
                Ptr<aodv_trust::AodvTrustRoutingProtocol> aodv = DynamicCast<aodv_trust::AodvTrustRoutingProtocol>(listProto);
                if (aodv)
                {
                    currentStream += aodv->AssignStreams(currentStream);
                    break;
                }
            }
        }
    }
    return (currentStream - stream);
}

} // namespace ns3