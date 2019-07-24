#pragma once

#include <string>
#include <event/Event.h>

class EventFactory
{
public:
  virtual ~EventFactory() = default;

  virtual const Event* factorFromString(const std::string& serializedEvent) const = 0 ;
};

