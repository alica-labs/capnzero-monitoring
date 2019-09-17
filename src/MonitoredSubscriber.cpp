#include <capnzero-base-msgs/string.capnp.h>
#include <ComplexMonitoredCallback.h>
#include <event/createevent.h>
#include "SimpleMonitoredCallback.h"
#include "MonitoredSubscriber.h"
#include "RelayEventProxy.h"
#include "event/GroupJoinEvent.h"
#include "event/ConnectEvent.h"
#include "event/SubscribeEvent.h"

MonitoredSubscriber::MonitoredSubscriber(void* zmqContext, capnzero::Protocol protocol, EventListener* listener) :
  subscriber(zmqContext, protocol), eventListener(listener)
{
  CreateEvent event(protocol);
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
  GroupJoinEvent event(topic);
  eventListener->notify(event);

  subscriber.setTopic(topic);
}

void MonitoredSubscriber::connect(const std::string& address)
{
  subscriber.addAddress(address);

  ConnectEvent event(address);
  eventListener->notify(event);
}

void MonitoredSubscriber::subscribe(void (* callback)(capnp::FlatArrayMessageReader&))
{
  MonitoredCallback* currentCallback = new SimpleMonitoredCallback(eventListener, callback);
  messageCallback.push_back(currentCallback);

  SubscribeEvent event;
  eventListener->notify(event);

  subscriber.subscribe(&MonitoredCallback::monitoredFunction, currentCallback);
}


