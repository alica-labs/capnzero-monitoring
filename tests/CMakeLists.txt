cmake_minimum_required( VERSION 3.13 )
project( capnzero-monitoring-test )

set(SOURCES
      acceptancetest.cpp
      eventlistenertest.cpp
      monitoredsubscribertest.cpp
      monitoredpublishertest.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME}
                            PUBLIC
                              ${CMAKE_CURRENT_SOURCE_DIR}/mocks
                              $<TARGET_PROPERTY:capnzero-monitoring,INTERFACE_INCLUDE_DIRECTORIES>
                              $<TARGET_PROPERTY:capnzero,INTERFACE_INCLUDE_DIRECTORIES>
)

target_link_libraries(${PROJECT_NAME}
                        PRIVATE
                          CONAN_PKG::gtest
                          capnzero-monitoring
                          capnzero
)

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_14)
