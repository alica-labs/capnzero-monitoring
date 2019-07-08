//
// Created by sst on 7/8/19.
//

#include <submodules/yaml-cpp/include/yaml-cpp/yaml.h>
#include "SendEvent.h"

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
