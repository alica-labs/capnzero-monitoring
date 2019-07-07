//
// Created by sst on 24.06.19.
//


#include <string.capnp.h>
#include "NetworkSocketEventListener.h"

NetworkSocketEventListener::NetworkSocketEventListener(void* zmqContext) : publisher(zmqContext)
{
  publisher.setDefaultGroup(MONITORING_GROUP);
  publisher.bind(capnzero::CommType::UDP, MONITORING_ADDRESS);
}

void NetworkSocketEventListener::notify(const std::string& message)
{
  capnp::MallocMessageBuilder builder;
  capnzero::String::Builder messageBuilder = builder.initRoot<capnzero::String>();
  messageBuilder.setString(message);

  publisher.send(builder);
}
