#include "subscribeeventfactory.h"

SubscribeEventFactory::SubscribeEventFactory()
{

}

const SubscribeEvent* SubscribeEventFactory::factorFromString(const std::string& serializedEvent) const
{
  return new SubscribeEvent();
}
