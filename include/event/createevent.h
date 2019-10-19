#pragma once

#include <capnzero/Common.h>
#include <event/event.h>

class CreateEvent : public Event
{
public:
  CreateEvent();

  CreateEvent(const std::string& id, capnzero::Protocol protocol);

  const std::string toYaml() const;

private:
  capnzero::Protocol protocol;
};
