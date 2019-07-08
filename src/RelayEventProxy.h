//
// Created by sst on 7/7/19.
//

#ifndef CAPNZEROMONITORINGLIB_RELAYEVENTPROXY_H
#define CAPNZEROMONITORINGLIB_RELAYEVENTPROXY_H


#include <capnzero/Publisher.h>
#include <src/event/Event.h>
#include "EventProxy.h"

class RelayEventProxy : public EventProxy
{
public:
  explicit RelayEventProxy(void* zmqContext);

  void notifyClient(const Event& event) override;

private:
  capnzero::Publisher publisher;
};


#endif //CAPNZEROMONITORINGLIB_RELAYEVENTPROXY_H
