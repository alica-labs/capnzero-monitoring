cmake_minimum_required(VERSION 3.10)

find_package(yaml-cpp REQUIRED)

set(SUBSCRIBER_EXE "monitored-subscriber")
set(PUBLISHER_EXE "monitored-publisher")
set(CLIENT_EXE "monitor-client")

set(SUBSCRIBER_SOURCES
  ${CMAKE_CURRENT_SOURCE_DIR}/monitored-subscriber/subscriber_main.cpp
  )

set(PUBLISHER_SOURCES
  ${CMAKE_CURRENT_SOURCE_DIR}/monitored-publisher/publisher_main.cpp
  )

set(CLIENT_SOURCES
  ${CMAKE_CURRENT_SOURCE_DIR}/monitor-client/client_main.cpp
  )

set(NEEDED_LIBS
      yaml-cpp
      capnzero
      capnzero-monitoring)

add_executable(${SUBSCRIBER_EXE} ${SUBSCRIBER_SOURCES})
target_link_libraries(${SUBSCRIBER_EXE} PRIVATE ${NEEDED_LIBS})

add_executable(${PUBLISHER_EXE} ${PUBLISHER_SOURCES})
target_link_libraries(${PUBLISHER_EXE} PRIVATE ${NEEDED_LIBS})

add_executable(${CLIENT_EXE} ${CLIENT_SOURCES})
target_link_libraries(${CLIENT_EXE} PRIVATE ${NEEDED_LIBS} capnzero-monitoring-client)
