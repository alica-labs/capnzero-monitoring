#include "Event.h"

#pragma once


class ReceiveEvent : public Event
{
public:
  ReceiveEvent(const std::string& message);

  const std::string toYaml() const override;

private:
  std::string message;
};

