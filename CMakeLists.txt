cmake_minimum_required(VERSION 3.13)
project(capnzeroMonitoringLib VERSION 1.0.0 LANGUAGES CXX)

add_compile_definitions(ZMQ_BUILD_DRAFT_API)

if(NOT EXISTS "${CMAKE_BINARY_DIR}/conan.cmake")
   message(STATUS "Downloading conan.cmake from https://github.com/conan-io/cmake-conan")
   file(DOWNLOAD "https://github.com/conan-io/cmake-conan/raw/v0.14/conan.cmake" "${CMAKE_BINARY_DIR}/conan.cmake")
endif()

include(${CMAKE_BINARY_DIR}/conan.cmake)

set(CONAN_REQUIREMENTS
    gtest/1.8.1@bincrafters/stable
    yaml-cpp/0.6.2@bincrafters/stable)

conan_cmake_run(REQUIRES ${CONAN_REQUIREMENTS}
                BASIC_SETUP CMAKE_TARGETS
                BUILD missing
                BUILD_TYPE Release
                GENERATORS cmake_find_package)

add_subdirectory(submodules/capnzero/capnzero)

set(SOURCES
     # Monitored publisher
     src/MonitoredPublisher.h
     src/MonitoredPublisher.cpp
     # Event listener
     src/EventListener.h
     src/NetworkSocketEventListener.h
     src/NetworkSocketEventListener.cpp
     # Monitor client
     src/MonitorClient.h
     src/MonitorClient.cpp
     # Monitored subscriber
     src/MonitoredSubscriber.h
     src/MonitoredSubscriber.cpp
     src/MonitoredCallback.cpp
     src/MonitoredCallback.h
     # Proxy
     src/EventProxy.h
     src/RelayEventProxy.cpp
     src/RelayEventProxy.h
     # Events
     src/event/Event.h
     src/event/GroupJoinEvent.cpp
     src/event/GroupJoinEvent.h
     src/event/ConnectEvent.cpp
     src/event/ConnectEvent.h
     src/event/SendEvent.cpp
     src/event/SendEvent.h
     src/event/BindEvent.cpp
     src/event/BindEvent.h
     src/event/SubscribeEvent.cpp
     src/event/SubscribeEvent.h
     src/event/ReceiveEvent.cpp
     src/event/ReceiveEvent.h
     )

add_library(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME}
                              PUBLIC
                                $<INSTALL_INTERFACE:include>
                                $<BUILD_INTERFACE:
                                  ${CMAKE_CURRENT_SOURCE_DIR}/include
                                  submodules/capnzero/capnzero/include
                                  ${CMAKE_CURRENT_SOURCE_DIR}/src>
                              PRIVATE
                                src
                           )

target_link_libraries(${PROJECT_NAME}
                          PRIVATE
                            pthread
                            CONAN_PKG::yaml-cpp
                            capnzero
                            capnzero-base-msgs)

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_14)

add_subdirectory(tests)
