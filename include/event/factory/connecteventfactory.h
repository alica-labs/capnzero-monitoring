#pragma once

#include <event/factory/eventfactory.h>
#include <event/connectevent.h>

class ConnectEventFactory : public EventFactory
{
public:
  ConnectEventFactory() = default;

  // EventFactory interface
public:
  const ConnectEvent* factorFromString(const std::string& serializedEvent) const;
};

