project(Plumpp)
cmake_minimum_required(VERSION 2.8)
set(CMAKE_CXX_FLAGS "-std=c++11 -Wall -g")
include_directories(${CMAKE_SOURCE_DIR})

set(Plumpp_HDRS
        Matrix.hpp
        Node.hpp
        Element.hpp
)

set(Plumpp_SRCS
        Matrix.cpp
        Node.cpp
        Element.cpp
)

add_library(core ${Plumpp_HDRS} ${Plumpp_SRCS})

set(test_SRCS
    tests/main.cpp
)
add_executable(test ${test_SRCS})
#target_link_libraries(test ${BOOST_UNIT_TEST_FRAMEWORK_LIBRARIES})
target_link_libraries(test core)
target_link_libraries(test /usr/local/lib/libboost_unit_test_framework.so)
