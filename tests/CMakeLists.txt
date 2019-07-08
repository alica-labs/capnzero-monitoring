cmake_minimum_required( VERSION 3.14 )
project( libzmqMonitoringTest )

set( CMAKE_CXX_STANDARD 14 )

find_package( GTest REQUIRED )

set( SOURCES
     test.cpp
     networkSocketEventListenerTest.cpp mocks/MockEventProxy.h mocks/MonitoredSubscriberTest.cpp )

add_executable( ${PROJECT_NAME} ${SOURCES} )

target_include_directories( ${PROJECT_NAME}
                              PRIVATE
                                ../include)

target_link_libraries( ${PROJECT_NAME}
                        PRIVATE
                          GTest::GTest
                          gmock
                          gmock_main
                          kj
                          capnp
                          capnzeroMonitoringLib)