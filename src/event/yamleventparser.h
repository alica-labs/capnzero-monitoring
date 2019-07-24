#include "Event.h"

#pragma once


class YamlEventParser
{
public:
  YamlEventParser();

  static const Event* parse(const std::string& yamlSerializedEvent);
};
