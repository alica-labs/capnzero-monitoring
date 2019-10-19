#pragma once

#include <eventlistener.h>
#include <monitoredcallback.h>
#include <functional>
#include <capnzero-base-msgs/string.capnp.h>
#include <event/receiveevent.h>

template<typename CallbackObjectType>
class ComplexMonitoredCallback : public MonitoredCallback
{
public:
  ComplexMonitoredCallback(const std::string& id, EventListener* eventListener,
                           void (CallbackObjectType::*callbackFunction)(::capnp::FlatArrayMessageReader&),
                           CallbackObjectType* callbackObject) :
    eventListener(eventListener), callbackFunction(callbackFunction), callbackObject(callbackObject), id(id)
  {
  }

  // MonitoredCallback interface
public:
  void monitoredFunction(capnp::FlatArrayMessageReader& reader) override
  {
    const std::string message = reader.getRoot<capnzero::String>().getString();

    callbackFunction(callbackObject, reader);

    ReceiveEvent event(id, message);
    eventListener->notify(event);
  }

private:
  EventListener* eventListener;
  std::function<void (CallbackObjectType*, capnp::FlatArrayMessageReader&)> callbackFunction;
  CallbackObjectType* callbackObject;
  std::string id;
};





