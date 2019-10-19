#pragma once

#include <eventlistener.h>
#include <monitoredcallback.h>
#include <functional>

class SimpleMonitoredCallback : public MonitoredCallback
{
public:
  SimpleMonitoredCallback(const std::string& id, EventListener* eventListener,
                          std::function<void(capnp::FlatArrayMessageReader&)> callback);

  void monitoredFunction(capnp::FlatArrayMessageReader& reader) override;

private:
  EventListener *eventListener;
  std::function<void (::capnp::FlatArrayMessageReader&)> callback;
  std::string id;
};

