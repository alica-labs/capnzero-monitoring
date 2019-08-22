#pragma once

#include <event/Event.h>

class GroupJoinEvent : public Event
{
public:
  GroupJoinEvent();

  GroupJoinEvent(const std::string& groupName);

  const std::string toYaml() const override;

  void parse(const std::string& yamlSerializedEvent) override;

private:
  std::string groupName;
};
