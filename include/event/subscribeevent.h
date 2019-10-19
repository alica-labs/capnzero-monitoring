#pragma once

#include <event/event.h>

class SubscribeEvent : public Event
{
public:
  SubscribeEvent(const std::string& id);

  const std::string toYaml() const override;
};
