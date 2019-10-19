#include <yaml-cpp/yaml.h>
#include <event/subscribeevent.h>

SubscribeEvent::SubscribeEvent(const std::string& id)
{
  this->id = id;
  type = "subscribe";
}

const std::string SubscribeEvent::toYaml() const
{
  YAML::Emitter yaml;
  yaml << YAML::BeginMap
       << YAML::Key << "id" << YAML::Value << id
       << YAML::Key << "type" << YAML::Value << type
       << YAML::EndMap;

  return yaml.c_str();
}
