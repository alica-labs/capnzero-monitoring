#pragma once

#include <event/Event.h>
#include <event/eventparser.h>
#include <capnzero/Subscriber.h>

class MonitorClient
{
public:
  MonitorClient(void* zmqContext,
                EventParser* eventParser,
                const std::string& monitoringAddress = "127.0.0.1:9876",
                const std::string& monitoringGroup = "monitoring");

  ~MonitorClient();

  void start();

  const std::vector<const Event*> retrieveEvents();

  void appendEvent(::capnp::FlatArrayMessageReader& reader);

private:
  capnzero::Subscriber subscriber;
  std::string monitoringAddress;
  std::string monitoringGroup;
  std::vector<const Event*> events;
  EventParser* eventParser;
};
