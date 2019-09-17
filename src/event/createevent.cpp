#include <event/createevent.h>
#include <yaml-cpp/yaml.h>

CreateEvent::CreateEvent()
{
  type = "create";
}

CreateEvent::CreateEvent(capnzero::Protocol protocol)
{
  type = "create";
}

const std::string CreateEvent::toYaml() const
{
  YAML::Emitter yaml;
  yaml << YAML::BeginMap
       << YAML::Key << "type" << YAML::Value << type
       << YAML::Key << "protocol" << YAML::Value << protocol
       << YAML::EndMap;

  return yaml.c_str();
}

void CreateEvent::parse(const std::string& yamlSerializedEvent)
{
  YAML::Node yamlEvent = YAML::Load(yamlSerializedEvent);
  int protocolOrdinal = yamlEvent["protocol"].as<int>();
  protocol = static_cast<capnzero::Protocol>(protocolOrdinal);
}
