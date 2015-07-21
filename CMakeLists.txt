cmake_minimum_required(VERSION 2.8)
project(smortest)

if(UNIX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=gnu++11 -fopenmp")
endif()

set(smortest_INCLUDES "${PROJECT_SOURCE_DIR}/src/include" "${PROJECT_SOURCE_DIR}/../eigen-3.2.5")

include_directories(${smortest_INCLUDES})

add_executable(smortest src/test1.cpp)
