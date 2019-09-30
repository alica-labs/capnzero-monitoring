#pragma once

#include <string>
#include <event/Event.h>
#include <EventListener.h>
#include <EventProxy.h>

class NetworkSocketEventListener : public EventListener
{
public:
  explicit NetworkSocketEventListener(EventProxy* proxy);

  ~NetworkSocketEventListener();

  void notify(const Event& event) override;

private:
  EventProxy* proxy;
};
