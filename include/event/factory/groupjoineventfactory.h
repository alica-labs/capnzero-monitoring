#pragma once

#include <event/factory/eventfactory.h>
#include <event/GroupJoinEvent.h>

class GroupJoinEventFactory : public EventFactory
{
public:
  GroupJoinEventFactory() = default;

  // EventFactory interface
public:
  const GroupJoinEvent* factorFromString(const std::string& serializedEvent) const;
};

