cmake_minimum_required(VERSION 3.10)
project(capnzero-monitoring-client VERSION 1.0.0 LANGUAGES CXX)

find_package(yaml-cpp REQUIRED)

set(SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/debugmonitorclient.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/debugeventproxy.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/debugeventlistener.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/debugeventhandler.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/capnzerodebugeventproxy.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/printdebugeventhandler.cpp
    )

add_library(${PROJECT_NAME} SHARED ${SOURCES})

target_include_directories(${PROJECT_NAME}
                              PUBLIC
                                $<INSTALL_INTERFACE:
                                  ${CMAKE_CURRENT_SOURCE_DIR}/include>
                                $<BUILD_INTERFACE:
                                  ${CMAKE_CURRENT_SOURCE_DIR}/include
                                  ${CMAKE_CURRENT_SOURCE_DIR}/src
                                  ${CMAKE_CURRENT_SOURCE_DIR}/submodules/capnzero/capnzero/include
                              PRIVATE
                                ${CMAKE_CURRENT_SOURCE_DIR}/src
                           )

target_link_libraries(${PROJECT_NAME}
                          PRIVATE
                            pthread
                            yaml-cpp
                            capnzero
                            capnzero-monitoring
                      )

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_14)
target_compile_options(${PROJECT_NAME} PRIVATE -fPIC)
target_compile_definitions(${PROJECT_NAME} PRIVATE ZMQ_BUILD_DRAFT_API)
