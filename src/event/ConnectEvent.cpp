//
// Created by sst on 7/8/19.
//

#include <yaml-cpp/yaml.h>
#include <event/ConnectEvent.h>

ConnectEvent::ConnectEvent()
{
  type = "connect";
}

ConnectEvent::ConnectEvent(const std::string& address, const capnzero::CommType commType) : address{address}, commType(commType)
{
  type = "connect";
}

const std::string ConnectEvent::toYaml() const
{
  YAML::Emitter yaml;
  yaml << YAML::BeginMap
       << YAML::Key << "type" << YAML::Value << type
       << YAML::Key << "address" << YAML::Value << address
       << YAML::Key << "communication_type" << YAML::Value << commType
       << YAML::EndMap;

  return yaml.c_str();
}

void ConnectEvent::parse(const std::string& yamlSerializedEvent)
{
  YAML::Node yamlEvent = YAML::Load(yamlSerializedEvent);
  address = yamlEvent["address"].as<std::string>();
  commType = static_cast<capnzero::CommType>(yamlEvent["communication_type"].as<int>());
}
