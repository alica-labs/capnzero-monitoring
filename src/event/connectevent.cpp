#include <yaml-cpp/yaml.h>
#include <event/connectevent.h>

ConnectEvent::ConnectEvent()
{
  type = "connect";
}

ConnectEvent::ConnectEvent(const std::string& address) : address{address}
{
  type = "connect";
}

const std::string ConnectEvent::toYaml() const
{
  YAML::Emitter yaml;
  yaml << YAML::BeginMap
       << YAML::Key << "type" << YAML::Value << type
       << YAML::Key << "address" << YAML::Value << address
       << YAML::EndMap;

  return yaml.c_str();
}

void ConnectEvent::parse(const std::string& yamlSerializedEvent)
{
  YAML::Node yamlEvent = YAML::Load(yamlSerializedEvent);
  address = yamlEvent["address"].as<std::string>();
}
