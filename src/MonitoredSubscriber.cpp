#include <capnzero-base-msgs/string.capnp.h>
#include <ComplexMonitoredCallback.h>
#include "SimpleMonitoredCallback.h"
#include "MonitoredSubscriber.h"
#include "RelayEventProxy.h"
#include "event/GroupJoinEvent.h"
#include "event/ConnectEvent.h"
#include "event/SubscribeEvent.h"

MonitoredSubscriber::MonitoredSubscriber(void* zmqContext, const std::string& group, EventListener* listener) :
  subscriber(zmqContext, group), eventListener(listener)
{
  GroupJoinEvent event(group);
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

void MonitoredSubscriber::connect(capnzero::CommType commType, const std::string& address)
{
  subscriber.connect(commType, address);

  ConnectEvent event(address, commType);
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


