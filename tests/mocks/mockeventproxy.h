//
// Created by sst on 7/7/19.
//

#include <eventproxy.h>
#include <gmock/gmock.h>

#ifndef CAPNZEROMONITORINGLIB_MOCKEVENTPROXY_H
#define CAPNZEROMONITORINGLIB_MOCKEVENTPROXY_H

class MockEventProxy : public EventProxy
{
public:
  MOCK_METHOD1(notifyClient, void(const Event&));
};

#endif //CAPNZEROMONITORINGLIB_MOCKEVENTPROXY_H

