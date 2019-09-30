#include <capnzero-base-msgs/string.capnp.h>
#include <relayeventproxy.h>

RelayEventProxy::RelayEventProxy(void* zmqContext, MonitorConfiguration monitorConfig):
  publisher(zmqContext, capnzero::Protocol::UDP), configuration(monitorConfig)
{
  publisher.setDefaultTopic(configuration.topic);
  publisher.addAddress(configuration.address);
}

void RelayEventProxy::notifyClient(const Event& event)
{
  const std::string message = event.toYaml();

  capnp::MallocMessageBuilder builder;
  capnzero::String::Builder messageBuilder = builder.initRoot<capnzero::String>();
  messageBuilder.setString(message);

  publisher.send(builder);
}
