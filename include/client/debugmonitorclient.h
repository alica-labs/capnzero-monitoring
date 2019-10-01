#pragma once

#include <client/capnzerodebugeventproxy.h>

class DebugMonitorClient
{
public:
  DebugMonitorClient(CapnzeroDebugEventProxy& proxy);

  void start();

  void stop();

  bool isRunning() const;

private:
  bool running;
  CapnzeroDebugEventProxy proxy;
};

