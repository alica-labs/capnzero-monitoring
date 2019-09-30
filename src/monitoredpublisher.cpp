#include <capnzero/Publisher.h>
#include <capnzero-base-msgs/string.capnp.h>
#include <monitoredpublisher.h>
#include <event/sendevent.h>
#include <event/addressevent.h>
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

void MonitoredPublisher::addAddress(const std::string& address)
{
  publisher.addAddress(address);

  AddressEvent event(address);
  eventListener->notify(event);
}

void MonitoredPublisher::send(const std::string& message, const std::string& topic)
{
  capnp::MallocMessageBuilder builder;
  capnzero::String::Builder messageBuilder = builder.initRoot<capnzero::String>();
  messageBuilder.setString(message);

  SendEvent event(message, topic);
  eventListener->notify(event);

  publisher.send(builder, topic);
}
