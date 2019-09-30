#pragma once

#include <debugeventhandler.h>

class PrintDebugEventHandler : public DebugEventHandler
{
public:
  PrintDebugEventHandler() = default;

  // DebugEventHandler interface
public:
  void handleDebugEvent(const Event* event);
};

