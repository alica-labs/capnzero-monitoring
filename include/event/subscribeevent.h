#pragma once

#include <event/event.h>

class SubscribeEvent : public Event
{
public:
  SubscribeEvent();

  const std::string toYaml() const override;

  void parse(const std::string& yamlSerializedEvent) override;
};
