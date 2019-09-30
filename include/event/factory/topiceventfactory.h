#pragma once

#include <event/factory/eventfactory.h>
#include <event/topicevent.h>

class TopicEventFactory : public EventFactory
{
public:
  TopicEventFactory() = default;

  // EventFactory interface
public:
  const TopicEvent* factorFromString(const std::string& serializedEvent) const;
};

