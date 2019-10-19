#include <event/createevent.h>
#include "simplemonitoredcallback.h"
#include "monitoredsubscriber.h"
#include "event/topicevent.h"
#include "event/addressevent.h"
#include "event/subscribeevent.h"

MonitoredSubscriber::MonitoredSubscriber(const std::string& id, void* zmqContext, capnzero::Protocol protocol, EventListener* listener) :
  subscriber(zmqContext, protocol), eventListener(listener), id(id)
{
  CreateEvent event(id, protocol);
  eventListener->notify(event);
}

MonitoredSubscriber::~MonitoredSubscriber()
{
  for(auto callback : messageCallback)
  {
   delete callback;
  }

  delete eventListener;
}

void MonitoredSubscriber::setTopic(const std::string& topic)
{
  TopicEvent event(id, topic);
  eventListener->notify(event);

  subscriber.setTopic(topic);
}

void MonitoredSubscriber::addAddress(const std::string& address)
{
  subscriber.addAddress(address);

  AddressEvent event(id, address);
  eventListener->notify(event);
}

void MonitoredSubscriber::subscribe(void (* callback)(capnp::FlatArrayMessageReader&))
{
  MonitoredCallback* currentCallback = new SimpleMonitoredCallback(id, eventListener, callback);
  messageCallback.push_back(currentCallback);

  SubscribeEvent event(id);
  eventListener->notify(event);

  subscriber.subscribe(&MonitoredCallback::monitoredFunction, currentCallback);
}


