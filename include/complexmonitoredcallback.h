#pragma once

#include <EventListener.h>
#include <MonitoredCallback.h>
#include <functional>
#include <capnzero-base-msgs/string.capnp.h>
#include <event/ReceiveEvent.h>

template<typename CallbackObjectType>
class ComplexMonitoredCallback : public MonitoredCallback
{
public:
  ComplexMonitoredCallback(EventListener* eventListener,
                           void (CallbackObjectType::*callbackFunction)(::capnp::FlatArrayMessageReader&),
                           CallbackObjectType* callbackObject) :
    eventListener(eventListener), callbackFunction(callbackFunction), callbackObject(callbackObject)
  {
  }

  // MonitoredCallback interface
public:
  void monitoredFunction(capnp::FlatArrayMessageReader& reader) override
  {
    const std::string message = reader.getRoot<capnzero::String>().getString();

    callbackFunction(callbackObject, reader);

    ReceiveEvent event(message);
    eventListener->notify(event);
  }

private:
  EventListener* eventListener;
  std::function<void (CallbackObjectType*, capnp::FlatArrayMessageReader&)> callbackFunction;
  CallbackObjectType* callbackObject;
};





