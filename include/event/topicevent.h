#pragma once

#include <event/event.h>

class TopicEvent : public Event
{
public:
  TopicEvent();

  TopicEvent(const std::string& id, const std::string& topic);

  const std::string toYaml() const override;

private:
  std::string topic;
};
