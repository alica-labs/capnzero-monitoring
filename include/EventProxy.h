#pragma once

#include <string>
#include <event/Event.h>

class EventProxy
{
public:
  virtual ~EventProxy() = default;

  virtual void notifyClient(const Event& event) = 0;
};
