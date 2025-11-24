/* --- MODIFIKASI AODV-TRUST: Helper Header --- */
#ifndef AODV_TRUST_HELPER_H
#define AODV_TRUST_HELPER_H

#include "ns3/aodv-trust-routing-protocol.h"
#include "ns3/ipv4-routing-helper.h"
#include "ns3/node-container.h"
#include "ns3/object-factory.h"

namespace ns3
{

class AodvTrustHelper : public Ipv4RoutingHelper
{
  public:
    AodvTrustHelper();

    /**
     * \returns pointer to clone of this AodvHelper
     *
     * \internal
     * This method is mainly for internal use by the other helpers;
     * clients are expected to free the dynamic memory allocated by this method
     */
    AodvTrustHelper* Copy() const override;

    /**
     * \param node the node on which the routing protocol will run
     * \returns a newly-created routing protocol
     *
     * This method will be called by ns3::InternetStackHelper::Install
     */
    Ptr<Ipv4RoutingProtocol> Create(Ptr<Node> node) const override;

    /**
     * \param name the name of the attribute to set
     * \param value the value of the attribute to set
     *
     * This method controls the attributes of ns3::aodv_trust::RoutingProtocol
     */
    void Set(std::string name, const AttributeValue& value);

    /**
     * Assign a fixed random variable stream number to the random variables
     * used by this model.  Return the number of streams (possibly zero) that
     * have been assigned.
     *
     * \param stream first stream index to use
     * \param c NodeContainer of the set of nodes for which the AodvRoutingProtocol
     * should be modified to use a fixed stream
     * \return the number of stream indices assigned by this model
     */
    int64_t AssignStreams(NodeContainer c, int64_t stream);

  private:
    ObjectFactory m_agentFactory;
};

} // namespace ns3

#endif /* AODV_TRUST_HELPER_H */