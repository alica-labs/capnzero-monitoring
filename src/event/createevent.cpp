#include <event/createevent.h>
#include <yaml-cpp/yaml.h>


CreateEvent::CreateEvent(const std::string& id, capnzero::Protocol protocol) : protocol(protocol)
{
  this->id = id;
  type = "create";
}

CreateEvent::CreateEvent()
{
  type = "create";
}

const std::string CreateEvent::toYaml() const
{
  YAML::Emitter yaml;
  yaml << YAML::BeginMap
       << YAML::Key << "id" << YAML::Value << id
       << YAML::Key << "type" << YAML::Value << type
       << YAML::Key << "protocol" << YAML::Value << protocol
       << YAML::EndMap;

  return yaml.c_str();
}
