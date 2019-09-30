#pragma once

#include <capnzero/Common.h>
#include <event/event.h>

class BindEvent : public Event
{
public:
  BindEvent();

  BindEvent(const std::string& address);

  const std::string toYaml() const override;

  void parse(const std::string& yamlSerializedEvent) override;

private:
  std::string address;
};
