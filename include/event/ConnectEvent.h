#pragma once

#include <capnzero/Common.h>
#include <event/Event.h>

class ConnectEvent : public Event
{
public:
  ConnectEvent();

  ConnectEvent(const std::string& address, const capnzero::CommType commType);

  const std::string toYaml() const;

  void parse(const std::string& yamlSerializedEvent) override;

private:
  std::string address;
  capnzero::CommType commType;
};
