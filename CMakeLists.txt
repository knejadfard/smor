cmake_minimum_required(VERSION 2.8)
project(smortest)

if(UNIX)
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=gnu++11")
endif()

set(smortest_INCLUDES "${PROJECT_SOURCE_DIR}/src/include")

include_directories(${smortest_INCLUDES})

add_executable(smortest src/main.cpp ${smortest_INCLUDES})
