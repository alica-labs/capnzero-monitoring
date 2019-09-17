#include <iostream>
#include <thread>
#include <capnp/serialize.h>
#include <capnzero-base-msgs/string.capnp.h>
#include <capnzero/Common.h>
#include <MonitorClient.h>
#include <event/yamleventparser.h>


MonitorClient::MonitorClient(void* zmqContext, EventParser* eventParser, const std::string& monitoringAddress, const std::string& monitoringGroup):
  subscriber(zmqContext, capnzero::Protocol::UDP), eventParser(eventParser), monitoringAddress {monitoringAddress}, monitoringGroup {monitoringGroup}
{}

MonitorClient::~MonitorClient()
{
  for(const Event* event : events)
  {
    delete event;
  }

  delete eventParser;
}

void MonitorClient::start()
{
  subscriber.addAddress(monitoringAddress);
  subscriber.setTopic(monitoringGroup);

  std::cout << "MONITOR_CLIENT connected to " << monitoringAddress << std::endl;

  subscriber.subscribe(&MonitorClient::appendEvent, this);
}

const std::vector<const Event*> MonitorClient::retrieveEvents()
{
  std::vector<const Event*> localEvents = events;

  events.clear();

  return localEvents;
}

void MonitorClient::appendEvent(capnp::FlatArrayMessageReader& reader)
{
  const std::string message = reader.getRoot<capnzero::String>().getString();

  std::cout << "MONITOR_CLIENT got event:" << std::endl << message << std::endl << std::endl;

  const Event* event = eventParser->parse(message);

  events.push_back(event);
}
