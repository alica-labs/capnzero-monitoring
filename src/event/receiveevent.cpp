#include <event/receiveevent.h>
#include <yaml-cpp/yaml.h>

ReceiveEvent::ReceiveEvent()
{
  type = "receive";
}

ReceiveEvent::ReceiveEvent(const std::string& id, const std::string& message) : message{message}
{
  this->id = id;
  type = "receive";
}

const std::string ReceiveEvent::toYaml() const
{
  YAML::Emitter yaml;
  yaml << YAML::BeginMap
       << YAML::Key << "id" << YAML::Value << id
       << YAML::Key << "type" << YAML::Value << type
       << YAML::Key << "message" << YAML::Value << message
       << YAML::EndMap;

  return yaml.c_str();
}
