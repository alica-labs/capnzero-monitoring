#pragma once

#include <event/Event.h>

class SubscribeEvent : public Event
{
public:
  SubscribeEvent();

  const std::string toYaml() const override;

  void parse(const std::string& yamlSerializedEvent) override;
};
