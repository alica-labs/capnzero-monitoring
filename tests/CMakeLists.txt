cmake_minimum_required( VERSION 3.14 )
project( libzmqMonitoringTest )

set( CMAKE_CXX_STANDARD 14 )

find_package( GTest REQUIRED )

if(NOT GTEST_FOUND)
  message("FATAL: GTest not found")
  return()
endif()

set( SOURCES
     test.cpp
     )

add_executable( ${PROJECT_NAME} ${SOURCES} )

target_include_directories( ${PROJECT_NAME}
                              PRIVATE
                                ${GTEST_INCLUDE_DIR}
                                ../include
                                ../capnzero/include)

target_link_libraries( ${PROJECT_NAME}
                        PRIVATE
                          ${GTEST_LIBRARIES}
                          gtest_main
                          kj
                          capnp
                          capnzeroMonitoringLib)