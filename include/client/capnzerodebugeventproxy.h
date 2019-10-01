#pragma once

#include <config/monitorconfiguration.h>
#include <capnzero/Subscriber.h>
#include <client/debugeventhandler.cpp>

class CapnzeroDebugEventProxy
{
public:
  CapnzeroDebugEventProxy(DebugEventHandler* handler, MonitorConfiguration config = MonitorConfiguration());

  ~CapnzeroDebugEventProxy();

  void startListening();

  void stopListening();

private:
  MonitorConfiguration configuration;
  DebugEventHandler* eventHandler;
  capnzero::Subscriber subscriber;
};

