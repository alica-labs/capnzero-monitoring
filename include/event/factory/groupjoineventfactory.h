#include "eventfactory.h"

#include <event/GroupJoinEvent.h>

#pragma once


class GroupJoinEventFactory : public EventFactory
{
public:
  GroupJoinEventFactory();

  // EventFactory interface
public:
  const GroupJoinEvent* factorFromString(const std::string& serializedEvent) const;
};

