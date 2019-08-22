#pragma once

#include <capnzero/Common.h>
#include <event/Event.h>

class BindEvent : public Event
{
public:
  BindEvent();

  BindEvent(const std::string& address, capnzero::CommType commType);

  const std::string toYaml() const override;

  void parse(const std::string& yamlSerializedEvent) override;

private:
  std::string address;
  capnzero::CommType commType;
};
