#include <event/factory/receiveeventfactory.h>

const ReceiveEvent* ReceiveEventFactory::factorFromString(const std::string& serializedEvent) const
{
  ReceiveEvent* event = new ReceiveEvent();
  event->parse(serializedEvent);
  return event;
}
