#include <capnzero-base-msgs/string.capnp.h>
#include <RelayEventProxy.h>

RelayEventProxy::RelayEventProxy(void* zmqContext, const std::string& monitoringGroup, const std::string& monitoringAddress) :
  publisher(zmqContext, capnzero::Protocol::UDP), monitoringGroup{monitoringGroup}, monitoringAddress{monitoringAddress}
{
  publisher.setDefaultTopic(monitoringGroup);
  publisher.addAddress(monitoringAddress);
}

void RelayEventProxy::notifyClient(const Event& event)
{
  const std::string message = event.toYaml();

  capnp::MallocMessageBuilder builder;
  capnzero::String::Builder messageBuilder = builder.initRoot<capnzero::String>();
  messageBuilder.setString(message);

  publisher.send(builder);
}
