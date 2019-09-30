#include <yaml-cpp/yaml.h>
#include <event/topicevent.h>

TopicEvent::TopicEvent()
{
  type = "topic";
}

TopicEvent::TopicEvent(const std::string& groupName) : topic{groupName}
{
  type = "topic";
}

const std::string TopicEvent::toYaml() const
{
  YAML::Emitter yaml;
  yaml << YAML::BeginMap
       << YAML::Key << "type" << YAML::Value << type
       << YAML::Key << "topic" << YAML::Value << topic
       << YAML::EndMap;

  return yaml.c_str();
}

void TopicEvent::parse(const std::string& yamlSerializedEvent)
{
  YAML::Node yamlEvent = YAML::Load(yamlSerializedEvent);
  topic = yamlEvent["topic"].as<std::string>();
}
