#pragma once

#include <EventListener.h>
#include <MonitoredCallback.h>
#include <functional>

class SimpleMonitoredCallback : public MonitoredCallback
{
public:
  SimpleMonitoredCallback(EventListener* eventListener, std::function<void(::capnp::FlatArrayMessageReader&)> callback);

  void monitoredFunction(capnp::FlatArrayMessageReader& reader) override;

private:
  EventListener *eventListener;
  std::function<void (::capnp::FlatArrayMessageReader&)> callback;
};

