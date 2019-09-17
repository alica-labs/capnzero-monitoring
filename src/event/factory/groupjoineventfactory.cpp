#include <event/factory/groupjoineventfactory.h>

const GroupJoinEvent* GroupJoinEventFactory::factorFromString(const std::string& serializedEvent) const
{
  GroupJoinEvent* event = new GroupJoinEvent();
  event->parse(serializedEvent);
  return event;
}
