#include "MonitoredCallback.h"
#include <capnzero-base-msgs/string.capnp.h>
#include <event/ReceiveEvent.h>

MonitoredCallback::MonitoredCallback(EventListener* eventListener, std::function<void (capnp::FlatArrayMessageReader&)> callback) :
  eventListener(eventListener), callback(callback)
{

}

void MonitoredCallback::monitoredCallback(capnp::FlatArrayMessageReader& reader)
{
  const std::string message = reader.getRoot<capnzero::String>().getString();

  ReceiveEvent event(message);
  eventListener->notify(event);

  callback(reader);
}
