#include "BindEvent.h"
#include "ConnectEvent.h"
#include "GroupJoinEvent.h"
#include "ReceiveEvent.h"
#include "SendEvent.h"
#include "SubscribeEvent.h"
#include "yamleventparser.h"

#include <yaml-cpp/yaml.h>

#include <exception/unknowneventexception.h>

YamlEventParser::YamlEventParser()
{}

Event* YamlEventParser::parse(const std::string& yamlSerializedEvent)
{
  YAML::Node yamlEvent = YAML::Load(yamlSerializedEvent);
  const std::string eventType = yamlEvent["type"].as<std::string>();

  if(eventType == "bind")
  {
    const std::string address = yamlEvent["address"].as<std::string>();
    capnzero::CommType commType = static_cast<capnzero::CommType>(yamlEvent["communication_type"].as<int>());
    return new BindEvent(address, commType);
  }
  else if(eventType == "connect")
  {
    const std::string address = yamlEvent["address"].as<std::string>();
    capnzero::CommType commType = static_cast<capnzero::CommType>(yamlEvent["communication_type"].as<int>());
    return new ConnectEvent(address, commType);
  }
  else if(eventType == "join")
  {
    const std::string group = yamlEvent["group"].as<std::string>();
    return new GroupJoinEvent(group);
  }
  else if(eventType == "receive")
  {
    const std::string message = yamlEvent["message"].as<std::string>();
    return new ReceiveEvent(message);
  }
  else if(eventType == "send")
  {
    const std::string message = yamlEvent["message"].as<std::string>();
    const std::string group = yamlEvent["group"].as<std::string>();
    return new SendEvent(message, group);
  }
  else if(eventType == "subscribe")
  {
    return new SubscribeEvent();
  }
  else
  {
    std::cout << "Unknown event of type \"" << eventType << "\" received." << std::endl;

    throw UnknownEventException("Unknown event of type \"" + eventType + "\"");
  }
}
