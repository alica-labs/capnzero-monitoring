#include <event/factory/sendeventfactory.h>

const SendEvent* SendEventFactory::factorFromString(const std::string& serializedEvent) const
{
  SendEvent* event = new SendEvent();
  event->parse(serializedEvent);
  return event;
}
