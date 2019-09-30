#include <gmock/gmock.h>
#include <eventlistener.h>

#pragma once

class MockEventListener : public EventListener
{
public:
  MOCK_METHOD1(notify, void(const Event&));
};

