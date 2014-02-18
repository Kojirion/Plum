project(Plumpp)
cmake_minimum_required(VERSION 2.8)
set(CMAKE_CXX_FLAGS "-std=c++11 -Wall -gdwarf-3")
include_directories(${CMAKE_SOURCE_DIR})

set(Plumpp_HDRS
        Node.hpp
        Element.hpp
        Mesh.hpp
        Algebra.hpp
)

set(Plumpp_SRCS
        Node.cpp
        Element.cpp
        Mesh.cpp
)

add_library(core ${Plumpp_HDRS} ${Plumpp_SRCS})

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} core)
target_link_libraries(${PROJECT_NAME} /usr/local/lib/libboost_program_options.so)
target_link_libraries(${PROJECT_NAME} /usr/lib/libarmadillo.so)

set(test_SRCS
    tests/main.cpp
)
add_executable(test ${test_SRCS})
#target_link_libraries(test ${BOOST_UNIT_TEST_FRAMEWORK_LIBRARIES})
target_link_libraries(test core)
target_link_libraries(test /usr/local/lib/libboost_unit_test_framework.so)
target_link_libraries(test /usr/lib/libarmadillo.so)
