#include <yaml-cpp/yaml.h>
#include <event/subscribeevent.h>

SubscribeEvent::SubscribeEvent()
{
  type = "subscribe";
}

const std::string SubscribeEvent::toYaml() const
{
  YAML::Emitter yaml;
  yaml << YAML::BeginMap
       << YAML::Key << "type" << YAML::Value << type
       << YAML::EndMap;

  return yaml.c_str();
}

void SubscribeEvent::parse(const std::string& yamlSerializedEvent)
{

}