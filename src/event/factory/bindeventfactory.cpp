#include <event/factory/bindeventfactory.h>

const BindEvent* BindEventFactory::factorFromString(const std::string& serializedEvent) const
{
  BindEvent* event = new BindEvent();
  event->parse(serializedEvent);
  return event;
}
