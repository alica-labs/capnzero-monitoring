#include <capnzero/Publisher.h>
#include <capnzero-base-msgs/string.capnp.h>
#include <MonitoredPublisher.h>
#include <event/SendEvent.h>
#include <event/BindEvent.h>
#include <event/createevent.h>

MonitoredPublisher::MonitoredPublisher(void* zmqContext, capnzero::Protocol protocol, EventListener* listener):
  publisher(zmqContext, protocol), eventListener(listener)
{
  CreateEvent event(protocol);
  eventListener->notify(event);
}

MonitoredPublisher::~MonitoredPublisher()
{
  delete eventListener;
}

void MonitoredPublisher::bind(const std::string& address)
{
  publisher.addAddress(address);

  BindEvent event(address);
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
