#pragma once

#include <capnp/serialize.h>

class MonitoredCallback
{
public:
  virtual ~MonitoredCallback() = default;

  virtual void monitoredFunction(capnp::FlatArrayMessageReader& reader) = 0;
};

