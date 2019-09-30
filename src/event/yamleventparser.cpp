#include <event/yamleventparser.h>
#include <yaml-cpp/yaml.h>
#include <exception/unknowneventexception.h>
#include <event/factory/bindeventfactory.h>
#include <event/factory/connecteventfactory.h>
#include <event/factory/createeventfactory.h>
#include <event/factory/eventfactory.h>
#include <event/factory/topiceventfactory.h>
#include <event/factory/receiveeventfactory.h>
#include <event/factory/sendeventfactory.h>
#include <event/factory/subscribeeventfactory.h>


YamlEventParser::YamlEventParser()
{
  eventMapping = {
    {"bind", new BindEventFactory()},
    {"connect", new ConnectEventFactory()},
    {"topic", new TopicEventFactory()},
    {"receive", new ReceiveEventFactory()},
    {"send", new SendEventFactory()},
    {"subscribe", new SubscribeEventFactory()},
    {"create", new CreateEventFactory()}
  };
}

YamlEventParser::~YamlEventParser()
{
  for(auto entry : eventMapping)
  {
    delete entry.second;
  }
}

const Event* YamlEventParser::parse(const std::string& yamlSerializedEvent)
{
  YAML::Node yamlEvent = YAML::Load(yamlSerializedEvent);
  const std::string eventType = yamlEvent["type"].as<std::string>();

  try
  {
    return eventMapping.at(eventType)->factorFromString(yamlSerializedEvent);
  }
  catch (std::out_of_range)
  {
    throw UnknownEventException("Unknown event of type \"" + eventType + "\"");
  }
}
