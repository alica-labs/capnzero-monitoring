//
// Created by sst on 7/7/19.
//

#ifndef CAPNZEROMONITORINGLIB_RELAYEVENTPROXY_H
#define CAPNZEROMONITORINGLIB_RELAYEVENTPROXY_H


#include <capnzero/Publisher.h>
#include "EventProxy.h"

class RelayEventProxy : public EventProxy
{
public:
  RelayEventProxy(void* zmqContext);

  void notifyClient(const std::string& message) override;

private:
  capnzero::Publisher publisher;
};


#endif //CAPNZEROMONITORINGLIB_RELAYEVENTPROXY_H
