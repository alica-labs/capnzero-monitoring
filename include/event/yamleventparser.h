#pragma once

#include <event/Event.h>
#include <event/eventparser.h>
#include <event/factory/eventfactory.h>
#include <map>

class YamlEventParser : public EventParser
{
public:
  YamlEventParser();
  ~YamlEventParser();

  const Event* parse(const std::string& yamlSerializedEvent) override;

private:
  std::map<const std::string, EventFactory*> eventMapping;
};
