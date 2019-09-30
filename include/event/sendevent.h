#pragma once

#include <event/event.h>

class SendEvent : public Event
{
public:
  SendEvent();

  SendEvent(const std::string& message, const std::string& groupName);

  const std::string toYaml() const override;

  void parse(const std::string& yamlSerializedEvent) override;

private:
  std::string message;
  std::string groupName;
};
