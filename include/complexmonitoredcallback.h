#pragma once

#include <eventlistener.h>
#include <monitoredcallback.h>
#include <functional>
#include <vector>
#include <capnzero-base-msgs/string.capnp.h>
#include <event/receiveevent.h>

template <typename CallbackObjectType>
class ComplexMonitoredCallback : public MonitoredCallback
{
public:
  ComplexMonitoredCallback(const std::string &id, std::vector<EventListener *> &eventListeners,
                           void (CallbackObjectType::*callbackFunction)(::capnp::FlatArrayMessageReader &),
                           CallbackObjectType *callbackObject)
      : eventListeners(eventListeners), callbackFunction(callbackFunction), callbackObject(callbackObject), id(id)
  {
  }

  // MonitoredCallback interface
public:
  void monitoredFunction(capnp::FlatArrayMessageReader &reader) override
  {
    const std::string message = reader.getRoot<capnzero::String>().getString();

    callbackFunction(callbackObject, reader);

    ReceiveEvent event(id, message);
    notifyEventListeners(event);
  }

private:
  std::vector<EventListener *> eventListeners;
  std::function<void(CallbackObjectType *, capnp::FlatArrayMessageReader &)> callbackFunction;
  CallbackObjectType *callbackObject;
  std::string id;

  void notifyEventListeners(Event &event) const
  {
    for (EventListener *listener : eventListeners)
    {
      listener->notify(event);
    }
  }
};
