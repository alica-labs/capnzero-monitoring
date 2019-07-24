#include "Event.h"

#pragma once


class YamlEventParser
{
public:
  YamlEventParser();

  static Event* parse(const std::string& yamlSerializedEvent);
};
