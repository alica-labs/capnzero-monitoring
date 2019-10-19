#include <event/addressevent.h>
#include <yaml-cpp/yaml.h>

AddressEvent::AddressEvent()
{
  type = "address";
}

AddressEvent::AddressEvent(const std::string& id, const std::string& address) : address{address}
{
  this->id = id;
  type = "address";
}

const std::string AddressEvent::toYaml() const
{
  YAML::Emitter yaml;
  yaml << YAML::BeginMap
       << YAML::Key << "id" << YAML::Value << id
       << YAML::Key << "type" << YAML::Value << type
       << YAML::Key << "address" << YAML::Value << address
       << YAML::EndMap;

  return yaml.c_str();
}
