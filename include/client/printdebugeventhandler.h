#pragma once

#include <client/debugeventhandler.h>

class PrintDebugEventHandler : public DebugEventHandler
{
public:
  PrintDebugEventHandler() = default;

  // DebugEventHandler interface
public:
  void handleDebugEvent(capnp::FlatArrayMessageReader& reader);
};

