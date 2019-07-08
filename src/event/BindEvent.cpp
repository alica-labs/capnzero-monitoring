//
// Created by sst on 7/8/19.
//

#include <yaml-cpp/yaml.h>
#include "BindEvent.h"

BindEvent::BindEvent(const std::string& address, const capnzero::CommType commType) : address{address},
                                                                                      commType(commType)
{
  type = "bind";
}

const std::string BindEvent::toYaml() const
{
  YAML::Emitter yaml;
  yaml << YAML::BeginMap
       << YAML::Key << "type" << YAML::Value << type
       << YAML::Key << "address" << YAML::Value << address
       << YAML::Key << "communication_type" << YAML::Value << commType
       << YAML::EndMap;

  return yaml.c_str();
}
