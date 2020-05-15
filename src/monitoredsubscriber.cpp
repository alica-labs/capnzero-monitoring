#include <event/createevent.h>
#include <simplemonitoredcallback.h>
#include <monitoredsubscriber.h>
#include <event/topicevent.h>
#include <event/addressevent.h>
#include <event/subscribeevent.h>

MonitoredSubscriber::MonitoredSubscriber(const std::string &id, void *zmqContext, capnzero::Protocol protocol)
    : subscriber(zmqContext, protocol), id(id)
{
}

MonitoredSubscriber::~MonitoredSubscriber()
{
  for (auto callback : messageCallback)
  {
    delete callback;
  }
}

void MonitoredSubscriber::attachEventListener(EventListener *listener)
{
  eventListeners.push_back(listener);
}

void MonitoredSubscriber::notifyEventListeners(Event &event) const
{
  for (EventListener *listener : eventListeners)
  {
    listener->notify(event);
  }
}

void MonitoredSubscriber::setTopic(const std::string &topic)
{
  TopicEvent event(id, topic);
  notifyEventListeners(event);

  subscriber.setTopic(topic);
}

void MonitoredSubscriber::addAddress(const std::string &address)
{
  subscriber.addAddress(address);

  AddressEvent event(id, address);
  notifyEventListeners(event);
}

void MonitoredSubscriber::subscribe(void (*callback)(capnp::FlatArrayMessageReader &))
{
  MonitoredCallback *currentCallback = new SimpleMonitoredCallback(id, eventListeners, callback);
  messageCallback.push_back(currentCallback);

  SubscribeEvent event(id);
  notifyEventListeners(event);

  subscriber.subscribe(&MonitoredCallback::monitoredFunction, currentCallback);
}
