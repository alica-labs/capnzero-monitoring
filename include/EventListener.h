#pragma once

#include <event/Event.h>

class EventListener
{
public:
  virtual ~EventListener() = default;

  virtual void notify(const Event& event) = 0;
};

