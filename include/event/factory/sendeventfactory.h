#pragma once

#include <event/factory/eventfactory.h>
#include <event/sendevent.h>

class SendEventFactory : public EventFactory
{
public:
  SendEventFactory() = default;

  // EventFactory interface
public:
  const SendEvent* factorFromString(const std::string& serializedEvent) const;
};

