#include <gmock/gmock.h>
#include <EventListener.h>

#pragma once

class MockEventListener : public EventListener
{
public:
  MOCK_METHOD1(notify, void(const Event&));
};

