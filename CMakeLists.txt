cmake_minimum_required(VERSION 3.13)
project(capnzero-monitoring VERSION 1.0.0 LANGUAGES CXX)

option(CATKIN_ENABLED "This enables the project to be built with a catkin workspace" OFF)

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

if(CATKIN_ENABLED)
  find_package(catkin REQUIRED COMPONENTS capnzero)

  catkin_package(
    INCLUDE_DIRS include ${catkin_INCLUDE_DIRS}
    LIBRARIES capnzero-monitoring
    CATKIN_DEPENDS capnzero
  )

  set(CAPNZERO_INCLUDES "${catkin_INCLUDE_DIRS}")
  set(CAPNZERO_LIBRARIES "${catkin_LIBRARIES}")
else()
  add_subdirectory(submodules/capnzero/capnzero)
  set(CAPNZERO_INCLUDES submodules/capnzero/capnzero/include)
  set(CAPNZERO_LIBRARIES capnzero capnzero-base-msgs)
endif()

set(SOURCES
     src/monitoredpublisher.cpp
     src/networksocketeventlistener.cpp
     src/monitoredsubscriber.cpp
     src/simplemonitoredcallback.cpp
     src/relayeventproxy.cpp
     src/event/topicevent.cpp
     src/event/sendevent.cpp
     src/event/subscribeevent.cpp
     src/event/receiveevent.cpp
     src/event/createevent.cpp
     src/event/addressevent.cpp
     src/exception/unknowneventexception.cpp
     src/config/monitorconfiguration.cpp
     )

add_library(${PROJECT_NAME} SHARED ${SOURCES})

target_include_directories(${PROJECT_NAME}
                              PUBLIC
                                $<INSTALL_INTERFACE:
                                  ${CMAKE_CURRENT_SOURCE_DIR}/include>
                                $<BUILD_INTERFACE:
                                  ${CMAKE_CURRENT_SOURCE_DIR}/include
                                  ${CMAKE_CURRENT_SOURCE_DIR}/src
                                  ${CAPNZERO_INCLUDES}
                              PRIVATE
                                src
                           )

target_link_libraries(${PROJECT_NAME}
                         PRIVATE
                          CONAN_PKG::yaml-cpp
                          capnzero)

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_14)
target_compile_options(${PROJECT_NAME} PRIVATE -fPIC)
target_compile_definitions(${PROJECT_NAME} PRIVATE ZMQ_BUILD_DRAFT_API)

add_subdirectory(tests)
add_subdirectory(example)
