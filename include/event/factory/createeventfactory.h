#pragma once

#include <event/factory/eventfactory.h>
#include <event/createevent.h>

class CreateEventFactory : public EventFactory
{
public:
  CreateEventFactory() = default;

  // EventFactory interface
public:
  const CreateEvent* factorFromString(const std::string& serializedEvent) const;
};

