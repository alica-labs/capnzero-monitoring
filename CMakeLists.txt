cmake_minimum_required(VERSION 3.13)
project(capnzeroMonitoring VERSION 1.0.0 LANGUAGES CXX)

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
     src/MonitoredPublisher.cpp
     src/NetworkSocketEventListener.cpp
     src/MonitorClient.cpp
     src/MonitoredSubscriber.cpp
     src/SimpleMonitoredCallback.cpp
     src/ComplexMonitoredCallback.cpp
     src/RelayEventProxy.cpp
     src/event/GroupJoinEvent.cpp
     src/event/ConnectEvent.cpp
     src/event/SendEvent.cpp
     src/event/BindEvent.cpp
     src/event/SubscribeEvent.cpp
     src/event/ReceiveEvent.cpp
     src/event/yamleventparser.cpp
     src/event/factory/bindeventfactory.cpp
     src/event/factory/connecteventfactory.cpp
     src/event/factory/connecteventfactory.cpp
     src/event/factory/groupjoineventfactory.cpp
     src/event/factory/receiveeventfactory.cpp
     src/event/factory/sendeventfactory.cpp
     src/event/factory/subscribeeventfactory.cpp
     src/exception/unknowneventexception.cpp
     )

add_library(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME}
                              PUBLIC
                                $<INSTALL_INTERFACE:
                                  ${CMAKE_CURRENT_SOURCE_DIR}/include>
                                $<BUILD_INTERFACE:
                                  ${CMAKE_CURRENT_SOURCE_DIR}/include
                                  ${CMAKE_CURRENT_SOURCE_DIR}/src
                                  submodules/capnzero/capnzero/include>
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
