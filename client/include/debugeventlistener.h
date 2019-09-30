#pragma once

#include <debugeventhandler.h>
#include <event/event.h>

class DebugEventListener
{
public:
  virtual ~DebugEventListener() = default;

  virtual void addEventHandler(DebugEventHandler* eventHandler) = 0;

  virtual void notify(Event* event) = 0;
};

