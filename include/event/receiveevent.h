#pragma once

#include <event/event.h>

class ReceiveEvent : public Event
{
public:
  ReceiveEvent();

  ReceiveEvent(const std::string& id, const std::string& message);

  const std::string toYaml() const override;

private:
  std::string message;
};

