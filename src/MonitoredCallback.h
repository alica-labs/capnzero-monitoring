#include "NetworkSocketEventListener.h"
#include <functional>

#pragma once


class MonitoredCallback
{
public:
  MonitoredCallback(EventListener *eventListener);

  void setCallback(std::function<void(::capnp::FlatArrayMessageReader&)> callback);

  void monitoredCallback(capnp::FlatArrayMessageReader& reader);

private:
  EventListener *eventListener;
  std::function<void (::capnp::FlatArrayMessageReader&)> callback;
};

