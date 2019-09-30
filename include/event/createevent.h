#pragma once

#include <capnzero/Common.h>
#include <event/event.h>

class CreateEvent : public Event
{
public:
  CreateEvent();

  CreateEvent(capnzero::Protocol protocol);

  const std::string toYaml() const;

  void parse(const std::string& yamlSerializedEvent) override;

private:
  capnzero::Protocol protocol;
};
