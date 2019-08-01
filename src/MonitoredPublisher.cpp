//
// Created by sst on 24.06.19.
//

#include <capnzero/CapnZero.h>
#include <capnzero-base-msgs/string.capnp.h>
#include "MonitoredPublisher.h"
#include <event/SendEvent.h>
#include <event/BindEvent.h>

MonitoredPublisher::MonitoredPublisher(void* zmqContext, EventListener* listener) :
  publisher(zmqContext), eventListener(listener)
{

}

MonitoredPublisher::~MonitoredPublisher()
{
  delete eventListener;
}

void MonitoredPublisher::bind(capnzero::CommType commType, const std::string& address)
{
  publisher.bind(commType, address);

  BindEvent event(address, commType);
  eventListener->notify(event);
}

void MonitoredPublisher::send(const std::string& message, const std::string& groupName)
{
  capnp::MallocMessageBuilder builder;
  capnzero::String::Builder messageBuilder = builder.initRoot<capnzero::String>();
  messageBuilder.setString(message);

  SendEvent event(message, groupName);
  eventListener->notify(event);

  publisher.send(builder, groupName);
}
