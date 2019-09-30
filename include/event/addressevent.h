#include "event.h"

#pragma once


class AddressEvent : public Event
{
public:
  AddressEvent();

  AddressEvent(const std::string& address);
  // Event interface
public:
  const std::string toYaml() const;
  void parse(const std::string& yamlSerializedEvent);

private:
  std::string address;
};

