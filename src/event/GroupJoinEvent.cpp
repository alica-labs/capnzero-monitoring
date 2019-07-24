//
// Created by sst on 7/8/19.
//

#include <yaml-cpp/yaml.h>
#include "GroupJoinEvent.h"

GroupJoinEvent::GroupJoinEvent()
{
  type = "join";
}

GroupJoinEvent::GroupJoinEvent(const std::string& groupName) : groupName{groupName}
{
  type = "join";
}

const std::string GroupJoinEvent::toYaml() const
{
  YAML::Emitter yaml;
  yaml << YAML::BeginMap
       << YAML::Key << "type" << YAML::Value << type
       << YAML::Key << "group" << YAML::Value << groupName
       << YAML::EndMap;

  return yaml.c_str();
}

void GroupJoinEvent::parse(const std::string& yamlSerializedEvent)
{
  YAML::Node yamlEvent = YAML::Load(yamlSerializedEvent);
  groupName = yamlEvent["group"].as<std::string>();
}
