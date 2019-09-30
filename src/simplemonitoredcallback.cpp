#include <SimpleMonitoredCallback.h>
#include <capnzero-base-msgs/string.capnp.h>
#include <event/ReceiveEvent.h>

SimpleMonitoredCallback::SimpleMonitoredCallback(EventListener* eventListener, std::function<void (capnp::FlatArrayMessageReader&)> callback) :
  eventListener(eventListener), callback(callback)
{
}

void SimpleMonitoredCallback::monitoredFunction(capnp::FlatArrayMessageReader& reader)
{
  const std::string message = reader.getRoot<capnzero::String>().getString();

  callback(reader);

  ReceiveEvent event(message);
  eventListener->notify(event);
}
