#pragma once

#include <complexmonitoredcallback.h>
#include <eventlistener.h>
#include <monitoredcallback.h>
#include <capnp/serialize.h>
#include <capnzero/Subscriber.h>
#include <event/subscribeevent.h>
#include <vector>

class MonitoredSubscriber
{
public:
  MonitoredSubscriber(const std::string& id, void* zmqContext, capnzero::Protocol protocol, EventListener* listener);

  ~MonitoredSubscriber();

  void addAddress(const std::string& address);

  void setTopic(const std::string& topic);

  void subscribe(void (* callbackFunction)(capnp::FlatArrayMessageReader&));

  template <typename CallbackObjectType>
  void subscribe(void (CallbackObjectType::*callbackFunction)(capnp::FlatArrayMessageReader&), CallbackObjectType* callbackObject)
  {
    MonitoredCallback* currentCallback = new ComplexMonitoredCallback<CallbackObjectType>(id, eventListener, callbackFunction, callbackObject);
    messageCallback.push_back(currentCallback);

    SubscribeEvent event(id);
    eventListener->notify(event);

    subscriber.subscribe(&MonitoredCallback::monitoredFunction, currentCallback);
  }

private:
  std::string id;
  capnzero::Subscriber subscriber;
  EventListener *eventListener;
  std::vector<MonitoredCallback*> messageCallback;
};
