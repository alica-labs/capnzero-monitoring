//
// Created by sst on 7/7/19.
//

#include <monitor_config.h>
#include <capnzero-base-msgs/string.capnp.h>
#include "RelayEventProxy.h"

RelayEventProxy::RelayEventProxy(void* zmqContext) : publisher(zmqContext)
{
  publisher.setDefaultGroup(MONITORING_GROUP);
  publisher.bind(capnzero::CommType::UDP, MONITORING_ADDRESS);
}

void RelayEventProxy::notifyClient(const Event& event)
{
  const std::string message = event.toYaml();
  
  capnp::MallocMessageBuilder builder;
  capnzero::String::Builder messageBuilder = builder.initRoot<capnzero::String>();
  messageBuilder.setString(message);

  publisher.send(builder);

}
