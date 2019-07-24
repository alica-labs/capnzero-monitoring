//
// Created by sst on 24.06.19.
//

#include <iostream>
#include <thread>
#include <capnp/serialize.h>
#include <capnzero-base-msgs/string.capnp.h>
#include <capnzero/Common.h>
#include <event/BindEvent.h>
#include <event/ConnectEvent.h>
#include <event/Event.h>
#include <event/GroupJoinEvent.h>
#include <event/ReceiveEvent.h>
#include <event/SendEvent.h>
#include <event/SubscribeEvent.h>
#include <yaml-cpp/yaml.h>
#include "MonitorClient.h"

MonitorClient::MonitorClient(void* zmqContext, const std::string& monitoringAddress, const std::string& monitoringGroup) :
  subscriber(zmqContext, monitoringGroup), monitoringAddress {monitoringAddress}, monitoringGroup {monitoringGroup}
{

}

MonitorClient::~MonitorClient()
{
  for(Event* event : events)
  {
    delete event;
  }
}

void MonitorClient::start()
{
  subscriber.connect(capnzero::CommType::UDP, monitoringAddress);

  std::cout << "MONITOR_CLIENT connected to " << monitoringAddress << std::endl;

  subscriber.subscribe(&MonitorClient::appendEvent, this);
}

const std::vector<Event*> MonitorClient::getEvents() const
{
  return events;
}

void MonitorClient::appendEvent(capnp::FlatArrayMessageReader& reader)
{
  const std::string message = reader.getRoot<capnzero::String>().getString();

  std::cout << "MONITOR_CLIENT got event:" << std::endl << message << std::endl << std::endl;

  YAML::Node serializedEvent = YAML::Load(message);
  const std::string eventType = serializedEvent["type"].as<std::string>();

  Event* event;

  if(eventType == "bind")
  {
    const std::string address = serializedEvent["address"].as<std::string>();
    capnzero::CommType commType = static_cast<capnzero::CommType>(serializedEvent["communication_type"].as<int>());
    event = new BindEvent(address, commType);
  }
  else if(eventType == "connect")
  {
    const std::string address = serializedEvent["address"].as<std::string>();
    capnzero::CommType commType = static_cast<capnzero::CommType>(serializedEvent["communication_type"].as<int>());
    event = new ConnectEvent(address, commType);
  }
  else if(eventType == "join")
  {
    const std::string group = serializedEvent["group"].as<std::string>();
    event = new GroupJoinEvent(group);
  }
  else if(eventType == "receive")
  {
    const std::string message = serializedEvent["message"].as<std::string>();
    event = new ReceiveEvent(message);
  }
  else if(eventType == "send")
  {
    const std::string message = serializedEvent["message"].as<std::string>();
    const std::string group = serializedEvent["group"].as<std::string>();
    event = new SendEvent(message, group);
  }
  else if(eventType == "subscribe")
  {
    event = new SubscribeEvent();
  }
  else
  {
    std::cout << "Unknown event of type \"" << eventType << "\" received." << std::endl;
    return;
  }

  events.push_back(event);
}
