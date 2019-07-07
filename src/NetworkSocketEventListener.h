//
// Created by sst on 24.06.19.
//

#ifndef LIBZMQMONITORING_SOCKETEVENTLISTENER_H
#define LIBZMQMONITORING_SOCKETEVENTLISTENER_H

#include <string>
#include <capnzero/CapnZero.h>
#include "monitor_config.h"

class NetworkSocketEventListener
{
public:
  NetworkSocketEventListener(void* zmqContext);

  void notify(const std::string& message);

private:
  capnzero::Publisher publisher;
};


#endif //LIBZMQMONITORING_SOCKETEVENTLISTENER_H
