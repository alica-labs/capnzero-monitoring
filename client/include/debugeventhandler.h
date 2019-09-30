#pragma once

#include <event/event.h>

class DebugEventHandler
{
public:
  virtual ~DebugEventHandler() = default;

  virtual void handleDebugEvent(const Event* event) = 0;
};

