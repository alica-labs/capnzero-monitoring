#include <event/factory/addresseventfactory.h>
#include <event/addressevent.h>

const Event* AddressEventFactory::factorFromString(const std::string& serializedEvent) const
{
  AddressEvent *event = new AddressEvent();
  event->parse(serializedEvent);
  return event;
}
