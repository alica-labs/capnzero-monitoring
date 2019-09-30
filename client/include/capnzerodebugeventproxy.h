#pragma once

#include <debugeventhandler.h>
#include <debugeventlistener.h>
#include <debugeventproxy.h>
#include <config/monitorconfiguration.h>
#include <capnzero/Subscriber.h>

class CapnzeroDebugEventProxy : public DebugEventListener, DebugEventProxy
{
public:
  CapnzeroDebugEventProxy(MonitorConfiguration config = MonitorConfiguration());

  // DebugEventProxy interface
public:
  void startListening();
  void stopListening();

  // DebugEventListener interface
public:
  void addEventHandler(DebugEventHandler* eventHandler);
  void notify(const Event* event);

private:
  void capnzeroCallback(capnp::FlatArrayMessageReader& reader);

private:
  MonitorConfiguration configuration;
  DebugEventHandler* eventHandler;
  capnzero::Subscriber subscriber;
};

