#pragma once

#include <string>
#include <event/event.h>
#include <eventlistener.h>
#include <eventproxy.h>

class NetworkSocketEventListener : public EventListener
{
public:
  explicit NetworkSocketEventListener(EventProxy *proxy);

  void notify(const Event &event) override;

private:
  EventProxy *proxy;
};
