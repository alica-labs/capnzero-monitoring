#include "connecteventfactory.h"

ConnectEventFactory::ConnectEventFactory()
{

}

const ConnectEvent* ConnectEventFactory::factorFromString(const std::string& serializedEvent) const
{
  ConnectEvent* event = new ConnectEvent();
  event->parse(serializedEvent);
  return event;
}
