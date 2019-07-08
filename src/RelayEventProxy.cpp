//
// Created by sst on 7/7/19.
//

#include <monitor_config.h>
#include <capnzero-base-msgs/string.capnp.h>
#include "RelayEventProxy.h"

void RelayEventProxy::notifyClient(const std::string& message)
{
  capnp::MallocMessageBuilder builder;
  capnzero::String::Builder messageBuilder = builder.initRoot<capnzero::String>();
  messageBuilder.setString(message);

  publisher.send(builder);
}

RelayEventProxy::RelayEventProxy(void* zmqContext) : publisher(zmqContext)
{
  publisher.setDefaultGroup(MONITORING_GROUP);
  publisher.bind(capnzero::CommType::UDP, MONITORING_ADDRESS);
}
