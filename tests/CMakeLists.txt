cmake_minimum_required( VERSION 3.13 )
project( capnzeroMonitoringTest )

set( SOURCES
     test.cpp
     networkSocketEventListenerTest.cpp
     MonitoredSubscriberTest.cpp
     monitoredpublishertest.cpp
     monitorclienttest.cpp
     eventparsertest.cpp
     mocks/MockEventProxy.h
     mocks/MockEventListener.h
     )

add_executable( ${PROJECT_NAME} ${SOURCES} )

target_include_directories( ${PROJECT_NAME} PRIVATE ../include mocks)

target_link_libraries( ${PROJECT_NAME}
                        PRIVATE
                          CONAN_PKG::gtest
                          capnp
                          capnzeroMonitoring)

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_14)
