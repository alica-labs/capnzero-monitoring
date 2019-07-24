#include "Event.h"

#pragma once


class ReceiveEvent : public Event
{
public:
  ReceiveEvent();

  ReceiveEvent(const std::string& message);

  const std::string toYaml() const override;

  void parse(const std::string& yamlSerializedEvent) override;

private:
  std::string message;
};

