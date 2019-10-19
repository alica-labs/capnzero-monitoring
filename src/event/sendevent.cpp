#include <yaml-cpp/yaml.h>
#include <event/sendevent.h>

SendEvent::SendEvent()
{
  type = "send";
}

SendEvent::SendEvent(const std::string& id, const std::string& message, const std::string& groupName) : message{message}, topic{groupName}
{
  this->id = id;
  type = "send";
}

const std::string SendEvent::toYaml() const
{
  YAML::Emitter yaml;
  yaml << YAML::BeginMap
       << YAML::Key << "id" << YAML::Value << id
       << YAML::Key << "type" << YAML::Value << type
       << YAML::Key << "message" << YAML::Value << message
       << YAML::Key << "topic" << YAML::Value << topic
       << YAML::EndMap;

  return yaml.c_str();
}
