#include <event/factory/createeventfactory.h>

const CreateEvent* CreateEventFactory::factorFromString(const std::string& serializedEvent) const
{
  CreateEvent* event = new CreateEvent();
  event->parse(serializedEvent);
  return event;
}
