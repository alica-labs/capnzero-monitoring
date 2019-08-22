#pragma once

#include <event/Event.h>

class EventParser
{
public:
  virtual ~EventParser() = default;

  virtual const Event* parse(const std::string& serializedEvent) = 0;
};

