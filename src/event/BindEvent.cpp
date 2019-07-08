//
// Created by sst on 7/8/19.
//

#include "BindEvent.h"

BindEvent::BindEvent(const std::string& address, const capnzero::CommType commType) : address{address},
                                                                                      commType(commType)
{
  type = "bind";
}

const std::string BindEvent::toYaml() const
{
  return "Bound socket to address " + address + " with communication type " + std::to_string(commType);
}
