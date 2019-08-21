#include <capnp/serialize.h>

#pragma once

class MonitoredCallback
{
public:
  virtual ~MonitoredCallback() = default;

  virtual void monitoredFunction(capnp::FlatArrayMessageReader& reader) = 0;
};

