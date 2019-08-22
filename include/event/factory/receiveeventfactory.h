#pragma once

#include <event/factory/eventfactory.h>
#include <event/ReceiveEvent.h>

class ReceiveEventFactory : public EventFactory
{
public:
  ReceiveEventFactory();

  // EventFactory interface
public:
  const ReceiveEvent* factorFromString(const std::string& serializedEvent) const;
};

