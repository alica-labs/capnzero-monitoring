#include <event/receiveevent.h>
#include <yaml-cpp/yaml.h>

ReceiveEvent::ReceiveEvent()
{
  type = "receive";
}

ReceiveEvent::ReceiveEvent(const std::string& message) : message{message}
{
  type = "receive";
}

const std::string ReceiveEvent::toYaml() const
{
  YAML::Emitter yaml;
  yaml << YAML::BeginMap
       << YAML::Key << "type" << YAML::Value << type
       << YAML::Key << "message" << YAML::Value << message
       << YAML::EndMap;

  return yaml.c_str();
}

void ReceiveEvent::parse(const std::string& yamlSerializedEvent)
{
  YAML::Node yamlEvent = YAML::Load(yamlSerializedEvent);
  message = yamlEvent["message"].as<std::string>();
}
