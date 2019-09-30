#include <event/factory/topiceventfactory.h>

const TopicEvent* TopicEventFactory::factorFromString(const std::string& serializedEvent) const
{
  TopicEvent* event = new TopicEvent();
  event->parse(serializedEvent);
  return event;
}
