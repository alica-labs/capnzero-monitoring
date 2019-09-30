#include <yaml-cpp/yaml.h>
#include <event/sendevent.h>

SendEvent::SendEvent()
{
  type = "send";
}

SendEvent::SendEvent(const std::string& message, const std::string& groupName) : message{message}, groupName{groupName}
{
  type = "send";
}

const std::string SendEvent::toYaml() const
{
  YAML::Emitter yaml;
  yaml << YAML::BeginMap
       << YAML::Key << "type" << YAML::Value << type
       << YAML::Key << "message" << YAML::Value << message
       << YAML::Key << "group" << YAML::Value << groupName
       << YAML::EndMap;

  return yaml.c_str();
}

void SendEvent::parse(const std::string& yamlSerializedEvent)
{
  YAML::Node yamlEvent = YAML::Load(yamlSerializedEvent);
  message = yamlEvent["message"].as<std::string>();
  groupName = yamlEvent["group"].as<std::string>();
}
