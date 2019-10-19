#include <yaml-cpp/yaml.h>
#include <event/topicevent.h>

TopicEvent::TopicEvent()
{
  type = "topic";
}


TopicEvent::TopicEvent(const std::string& id, const std::string& topic)
{
  this->id = id;
  type = "topic";
  this->topic = topic;
}


const std::string TopicEvent::toYaml() const
{
  YAML::Emitter yaml;
  yaml << YAML::BeginMap
       << YAML::Key << "id" << YAML::Value << id
       << YAML::Key << "type" << YAML::Value << type
       << YAML::Key << "topic" << YAML::Value << topic
       << YAML::EndMap;

  return yaml.c_str();
}
