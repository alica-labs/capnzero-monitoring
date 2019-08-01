//
// Created by sst on 7/7/19.
//

#ifndef CAPNZEROMONITORINGLIB_EVENTPROXY_H
#define CAPNZEROMONITORINGLIB_EVENTPROXY_H


#include <string>
#include <event/Event.h>

class EventProxy
{
public:
  virtual ~EventProxy() = default;

  virtual void notifyClient(const Event& event) = 0;
};


#endif //CAPNZEROMONITORINGLIB_EVENTPROXY_H
