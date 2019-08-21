#pragma once

#include "ComplexMonitoredCallback.h"

#include <EventListener.h>
#include <MonitoredCallback.h>
#include <capnp/serialize.h>
#include <capnzero/Subscriber.h>
#include <event/SubscribeEvent.h>
#include <vector>

class MonitoredSubscriber
{
public:
  MonitoredSubscriber(void* zmqContext, const std::string& group, EventListener* listener);

  ~MonitoredSubscriber();

  void connect(capnzero::CommType commType, const std::string& address);

  void subscribe(void (* callbackFunction)(capnp::FlatArrayMessageReader&));

  template <typename CallbackObjectType>
  void subscribe(void (CallbackObjectType::*callbackFunction)(capnp::FlatArrayMessageReader&), CallbackObjectType* callbackObject)
  {
    MonitoredCallback* currentCallback = new ComplexMonitoredCallback<CallbackObjectType>(eventListener, callbackFunction, callbackObject);
    messageCallback.push_back(currentCallback);

    SubscribeEvent event;
    eventListener->notify(event);

    subscriber.subscribe(&MonitoredCallback::monitoredFunction, currentCallback);
  }

private:
  capnzero::Subscriber subscriber;
  EventListener *eventListener;
  std::vector<MonitoredCallback*> messageCallback;
};
