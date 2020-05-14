#pragma once

#include <eventlistener.h>
#include <monitoredcallback.h>
#include <functional>
#include <vector>

class SimpleMonitoredCallback : public MonitoredCallback
{
public:
  SimpleMonitoredCallback(const std::string &id, std::vector<EventListener *> &eventListeners,
                          std::function<void(capnp::FlatArrayMessageReader &)> callback);

  void monitoredFunction(capnp::FlatArrayMessageReader &reader) override;

private:
  std::vector<EventListener *> eventListeners;
  std::function<void(::capnp::FlatArrayMessageReader &)> callback;
  std::string id;

  void notifyEventListeners(Event &event) const;
};
