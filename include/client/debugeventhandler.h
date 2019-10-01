#pragma once

#include <capnp/serialize.h>

class DebugEventHandler
{
public:
  virtual ~DebugEventHandler() = default;

  virtual void handleDebugEvent(capnp::FlatArrayMessageReader& reader) = 0;
};

