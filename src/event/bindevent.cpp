#include <yaml-cpp/yaml.h>
#include <event/bindevent.h>

BindEvent::BindEvent()
{
  type = "bind";
}

BindEvent::BindEvent(const std::string& address) : address{address}
{
  type = "bind";
}

const std::string BindEvent::toYaml() const
{
  YAML::Emitter yaml;
  yaml << YAML::BeginMap
       << YAML::Key << "type" << YAML::Value << type
       << YAML::Key << "address" << YAML::Value << address
       << YAML::EndMap;

  return yaml.c_str();
}

void BindEvent::parse(const std::string& yamlSerializedEvent)
{
  YAML::Node yamlEvent = YAML::Load(yamlSerializedEvent);
  address = yamlEvent["address"].as<std::string>();
}
