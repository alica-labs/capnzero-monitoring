cmake_minimum_required( VERSION 3.14 )
project( capnzeroMonitoringLib VERSION 1.0.0 LANGUAGES CXX )

add_compile_definitions( ZMQ_BUILD_DRAFT_API )

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
                                $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
                              PRIVATE
                                ${CMAKE_CURRENT_SOURCE_DIR}/src
                                ${CMAKE_CURRENT_SOURCE_DIR}/capnzero/include
                           )

target_link_libraries( ${PROJECT_NAME}
                          PRIVATE
                            pthread
                            zmq
                            ${PROJECT_SOURCE_DIR}/capnzero/lib/libcapnzero.a
                            ${PROJECT_SOURCE_DIR}/capnzero/lib/libcapnzero-base-msgs.a)

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_14)

add_subdirectory( tests )
