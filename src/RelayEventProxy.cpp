#include <capnzero-base-msgs/string.capnp.h>
#include <RelayEventProxy.h>

RelayEventProxy::RelayEventProxy(void* zmqContext, const std::string& monitoringGroup, const std::string& monitoringAddress) :
  publisher(zmqContext), monitoringGroup{monitoringGroup}, monitoringAddress{monitoringAddress}
{
  publisher.setDefaultGroup(monitoringGroup);
  publisher.bind(capnzero::CommType::UDP, monitoringAddress);
}

void RelayEventProxy::notifyClient(const Event& event)
{
  const std::string message = event.toYaml();

  capnp::MallocMessageBuilder builder;
  capnzero::String::Builder messageBuilder = builder.initRoot<capnzero::String>();
  messageBuilder.setString(message);

  publisher.send(builder);
}
