#pragma once

#include <event/event.h>

class TopicEvent : public Event
{
public:
  TopicEvent();

  TopicEvent(const std::string& topic);

  const std::string toYaml() const override;

  void parse(const std::string& yamlSerializedEvent) override;

private:
  std::string topic;
};
