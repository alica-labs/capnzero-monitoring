#pragma once

#include <event/Event.h>
#include <event/eventparser.h>
#include <capnzero/Subscriber.h>
#include <config/monitorconfiguration.h>

class MonitorClient
{
public:
  MonitorClient(void* zmqContext, EventParser* eventParser, MonitorConfiguration monitorConfig = MonitorConfiguration());

  ~MonitorClient();

  void start();

  const std::vector<const Event*> retrieveEvents();

  void appendEvent(::capnp::FlatArrayMessageReader& reader);

private:
  capnzero::Subscriber subscriber;
  MonitorConfiguration configuration;
  std::vector<const Event*> events;
  EventParser* eventParser;
};
