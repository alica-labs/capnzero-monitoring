//
// Created by sst on 24.06.19.
//

#include <CapnZero.h>
#include <string.capnp.h>
#include "MonitoredPublisher.h"

MonitoredPublisher::MonitoredPublisher(void* zmqContext, const std::string& groupName) :
publisher(zmqContext), eventListener(zmqContext)
{
  publisher.setDefaultGroup(groupName);
  eventListener.notify("LOG: new publisher on group " + groupName);
}

void MonitoredPublisher::bind(capnzero::CommType commType, const std::string& address)
{
  publisher.bind(commType, address);

  eventListener.notify("LOG: Publisher bound to address " + address + " with communication type " + std::to_string(commType));
}

void MonitoredPublisher::send(const std::string& message)
{
  capnp::MallocMessageBuilder builder;
  capnzero::String::Builder messageBuilder = builder.initRoot<capnzero::String>();
  messageBuilder.setString(message);

  publisher.send(builder);

  eventListener.notify("LOG: Publisher sent message \"" + message + "\"" );
}
