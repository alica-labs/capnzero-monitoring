//
// Created by sst on 7/8/19.
//

#include "GroupJoinEvent.h"

GroupJoinEvent::GroupJoinEvent(const std::string& groupName) : groupName{groupName}
{
  type = "join";
}

const std::string GroupJoinEvent::toYaml() const
{
  return "join " + groupName;
}
