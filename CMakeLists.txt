project(Plumpp)
cmake_minimum_required(VERSION 2.8)

find_package(Boost COMPONENTS program_options unit_test_framework REQUIRED)
find_package(Armadillo REQUIRED)


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
include_directories(${CMAKE_SOURCE_DIR})
include_directories(${Boost_INCLUDE_DIRS})
include_directories(${ARMADILLO_INCLUDE_DIRS})

set(HDRS
    Node.hpp
    Element.hpp
    Mesh.hpp
    Algebra.hpp
)

set(SRCS
    Node.cpp
    Element.cpp
    Mesh.cpp
)

add_library(core ${HDRS} ${SRCS})

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} core ${ARMADILLO_LIBRARIES} ${Boost_LIBRARIES})

set(test_SRCS
    tests/main.cpp
)

add_executable(unit_tests ${test_SRCS})
target_link_libraries(unit_tests core ${ARMADILLO_LIBRARIES} ${Boost_LIBRARIES})
