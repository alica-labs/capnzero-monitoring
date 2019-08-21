#include <EventListener.h>
#include <functional>
#include <MonitoredCallback.h>

#pragma once

class SimpleMonitoredCallback : public MonitoredCallback
{
public:
  SimpleMonitoredCallback(EventListener* eventListener, std::function<void(::capnp::FlatArrayMessageReader&)> callback);

  void monitoredFunction(capnp::FlatArrayMessageReader& reader) override;

private:
  EventListener *eventListener;
  std::function<void (::capnp::FlatArrayMessageReader&)> callback;
};

