//
// Created by sst on 7/8/19.
//

#include "SendEvent.h"

SendEvent::SendEvent(const std::string& message, const std::string& groupName) : message{message}, groupName{groupName}
{
  type = "send";
}

const std::string SendEvent::toYaml() const
{
  return "sending message \"" + message + "\" to group " + groupName;
}
