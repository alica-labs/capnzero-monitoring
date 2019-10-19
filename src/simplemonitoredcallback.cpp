#include <simplemonitoredcallback.h>
#include <capnzero-base-msgs/string.capnp.h>
#include <event/receiveevent.h>

SimpleMonitoredCallback::SimpleMonitoredCallback(const std::string& id, EventListener* eventListener,
                                                 std::function<void(capnp::FlatArrayMessageReader&)> callback) :
eventListener(eventListener), callback(callback), id(id)
{
}

void SimpleMonitoredCallback::monitoredFunction(capnp::FlatArrayMessageReader& reader)
{
  const std::string message = reader.getRoot<capnzero::String>().getString();

  callback(reader);

  ReceiveEvent event(id, message);
  eventListener->notify(event);
}
