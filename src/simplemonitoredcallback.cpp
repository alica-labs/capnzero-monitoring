#include <simplemonitoredcallback.h>
#include <capnzero-base-msgs/string.capnp.h>
#include <event/receiveevent.h>

SimpleMonitoredCallback::SimpleMonitoredCallback(const std::string &id, std::vector<EventListener *> &eventListeners,
                                                 std::function<void(capnp::FlatArrayMessageReader &)> callback)
    : eventListeners(eventListeners), callback(callback), id(id)
{
}

void SimpleMonitoredCallback::monitoredFunction(capnp::FlatArrayMessageReader &reader)
{
  const std::string message = reader.getRoot<capnzero::String>().getString();

  callback(reader);

  ReceiveEvent event(id, message);
  notifyEventListeners(event);
}

void SimpleMonitoredCallback::notifyEventListeners(Event &event) const
{
  for (EventListener *listener : eventListeners)
  {
    listener->notify(event);
  }
}