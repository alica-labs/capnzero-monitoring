#pragma once

#include <event/event.h>

class AddressEvent : public Event
{
public:
  AddressEvent();

  AddressEvent(const std::string &id, const std::string &address);
  // Event interface
public:
  const std::string toYaml() const;

private:
  std::string address;
};
