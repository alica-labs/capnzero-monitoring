#include "ReceiveEvent.h"

#include <yaml-cpp/yaml.h>

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
