#pragma once

#include <event/factory/eventfactory.h>
#include <event/receiveevent.h>

class ReceiveEventFactory : public EventFactory
{
public:
  ReceiveEventFactory() = default;

  // EventFactory interface
public:
  const ReceiveEvent* factorFromString(const std::string& serializedEvent) const;
};

