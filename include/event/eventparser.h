#pragma once

#include <event/event.h>

class EventParser
{
public:
  virtual ~EventParser() = default;

  virtual const Event* parse(const std::string& serializedEvent) = 0;
};

