#include "MonitoredCallback.h"
#include <capnzero-base-msgs/string.capnp.h>
#include <event/ReceiveEvent.h>

MonitoredCallback::MonitoredCallback(EventListener* eventListener) : eventListener(eventListener)
{

}

void MonitoredCallback::setCallback(std::function<void(capnp::FlatArrayMessageReader&)> callback)
{
  this->callback = callback;
}

void MonitoredCallback::monitoredCallback(capnp::FlatArrayMessageReader& reader)
{
  std::cout << "GOT MESSAGE IN CALLBACK: " << std::endl;
  const std::string message = reader.getRoot<capnzero::String>().getString();
  ReceiveEvent event(message);

  eventListener->notify(event);

  callback(reader);
}
