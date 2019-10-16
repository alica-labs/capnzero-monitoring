# capnzero-monitoring

Capnzero-Monitoring is an extension library that builds on top of the capnzero framework.

It enables event based monitoring on a capnzero enabled network.
The library attaches a listener to the publisher and subscriber of the Capnzero framework which triggers socket events missing from the ZeroMQ library.
The socket events are sent to a configured address via a proxy.

## Needed Tools

- conan
- cmake
- make
- optional: catkin

## Build

It is possible to build the library with plain cmake as well as with a catkin workspace.

However, before building be sure to initialize the submodules with

```shell
git submodule update --init
```

For building it with plain cmake simply invoke:

```shell
cmake . && make -j<number_of_cores>
```

For building it with catkin, enable the "CATKIN_ENABLED" cmake-option at build time.

```shell
catkin_make --force-cmake --cmake-args -DCATKIN_ENABLED=ON
```

## Usage

The publisher and subscriber entities have to be used as replacements for the original capnzero publisher and subscriber in an agent's implementation.

When properly initialized, the listener attached to the components will monitor creation, address change, subscription and toic change of a component as well as disipatch and receipt of messages.
The socket events are serialized in YAML.

The configuration of the destination address for the emitted socket events is done in the `Configuration` class.
The configuration is injected in the proxy at build time.
If no configuration has been supplied, the proxy defaults to the destination address `localhost:9876` and the destination topic `monitoring`.

A client implementation for accessing the sent socket events can be found [here](https://github.com/dasys-lab/capnzero-monitoring-client).

Another simple way to access the socket events is to bind a Capnzero subscriber to the configured destination address.
