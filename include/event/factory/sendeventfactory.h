#pragma once

#include <event/factory/eventfactory.h>
#include <event/SendEvent.h>

class SendEventFactory : public EventFactory
{
public:
  SendEventFactory();

  // EventFactory interface
public:
  const SendEvent* factorFromString(const std::string& serializedEvent) const;
};

