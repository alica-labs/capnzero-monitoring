#pragma once

#include <debugeventproxy.h>

class DebugMonitorClient
{
public:
  DebugMonitorClient(DebugEventProxy* proxy);

  ~DebugMonitorClient();

  void start();

  void stop();

  bool isRunning() const;

private:
  bool running;
  DebugEventProxy* proxy;
};

