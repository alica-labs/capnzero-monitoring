#include <event/addressevent.h>
#include <yaml-cpp/yaml.h>

AddressEvent::AddressEvent()
{
  type = "address";
}

AddressEvent::AddressEvent(const std::string& address) : address{address}
{
  type = "address";
}

const std::string AddressEvent::toYaml() const
{
  YAML::Emitter yaml;
  yaml << YAML::BeginMap
       << YAML::Key << "type" << YAML::Value << type
       << YAML::Key << "address" << YAML::Value << address
       << YAML::EndMap;

  return yaml.c_str();
}

void AddressEvent::parse(const std::string& yamlSerializedEvent)
{
  YAML::Node yamlEvent = YAML::Load(yamlSerializedEvent);
  address = yamlEvent["address"].as<std::string>();
}