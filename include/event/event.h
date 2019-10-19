#pragma once

#include <string>

class Event
{
public:
  virtual ~Event() = default;

  virtual const std::string toYaml() const = 0;

protected:
  std::string type;
  std::string id;
};
