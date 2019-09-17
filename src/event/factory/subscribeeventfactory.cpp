#include <event/factory/subscribeeventfactory.h>

const SubscribeEvent* SubscribeEventFactory::factorFromString(const std::string& serializedEvent) const
{
  return new SubscribeEvent();
}
