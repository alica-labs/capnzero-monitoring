#pragma once

#include <event/factory/eventfactory.h>
#include <event/GroupJoinEvent.h>

class TopicEventFactory : public EventFactory
{
public:
  TopicEventFactory() = default;

  // EventFactory interface
public:
  const TopicEvent* factorFromString(const std::string& serializedEvent) const;
};

