#include "Event.h"
#include <event/factory/eventfactory.h>
#include <map>

#pragma once


class YamlEventParser
{
public:
  YamlEventParser();
  ~YamlEventParser();

  const Event* parse(const std::string& yamlSerializedEvent);

private:
  std::map<const std::string, EventFactory*> eventMapping;
};
