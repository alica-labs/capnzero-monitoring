#include <event/Event.h>

#pragma once


class EventListener
{
public:
  virtual ~EventListener() = default;

  virtual void notify(const Event& event) = 0;
};

