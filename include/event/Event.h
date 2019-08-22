#pragma once

#include <string>

class Event
{
public:
  virtual ~Event() = default;

  virtual const std::string toYaml() const = 0;

  virtual void parse(const std::string& yamlSerializedEvent) = 0;

protected:
  std::string type;
};
