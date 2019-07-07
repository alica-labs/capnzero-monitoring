//
// Created by sst on 24.06.19.
//

#include <iostream>
#include <thread>
#include <capnp/serialize.h>
#include <string.capnp.h>
#include <Common.h>
#include "MonitorClient.h"

static void callback(capnp::FlatArrayMessageReader& reader)
{
  const std::string message = reader.getRoot<capnzero::String>().getString();

  std::cout << "MONITOR_CLIENT got message \"" << message << "\"" << std::endl;
}

MonitorClient::MonitorClient(void* zmqContext) : subscriber(zmqContext, MONITORING_GROUP)
{
}

void MonitorClient::start()
{
  subscriber.connect(capnzero::CommType::UDP, MONITORING_ADDRESS);

  std::cout << "MONITOR_CLIENT connected to " << MONITORING_ADDRESS << std::endl;

  subscriber.subscribe(&callback);
}
