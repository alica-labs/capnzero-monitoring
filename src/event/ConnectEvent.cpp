//
// Created by sst on 7/8/19.
//

#include "ConnectEvent.h"

ConnectEvent::ConnectEvent(const std::string& address, const capnzero::CommType commType) : address{address}, commType(commType)
{
  type = "connect";
}

const std::string ConnectEvent::toYaml() const
{
  return "connect on " + address + " with type " + std::to_string(commType);
}
