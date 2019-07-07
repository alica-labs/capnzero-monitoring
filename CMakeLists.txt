cmake_minimum_required( VERSION 3.14 )
project( capnzeroMonitoringLib VERSION 1.0.0 LANGUAGES CXX )

add_compile_definitions( ZMQ_BUILD_DRAFT_API )

add_subdirectory(submodules/capnzero/capnzero)

set( SOURCES
     src/MonitoredPublisher.h
     src/MonitoredPublisher.cpp
     src/NetworkSocketEventListener.h
     src/NetworkSocketEventListener.cpp
     src/MonitorClient.h
     src/MonitorClient.cpp
     src/MonitoredSubscriber.h
     src/MonitoredSubscriber.cpp
     )

add_library( ${PROJECT_NAME} ${SOURCES} )

target_include_directories(${PROJECT_NAME}
                              PUBLIC
                                $<INSTALL_INTERFACE:include>
                                $<BUILD_INTERFACE:
                                  ${CMAKE_CURRENT_SOURCE_DIR}/include
                                  submodules/capnzero/capnzero/include>
                              PRIVATE
                                src
                           )

target_link_libraries( ${PROJECT_NAME}
                          PRIVATE
                            pthread
                            zmq
                            capnzero
                            capnzero-base-msgs)

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_14)

add_subdirectory( tests )
