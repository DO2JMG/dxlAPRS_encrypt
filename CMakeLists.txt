cmake_minimum_required(VERSION 3.5)

project (encrypt)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")

include_directories(include)

find_package(CURL REQUIRED)

set(SOURCES
    src/main.cpp
)

add_executable(encrypt ${SOURCES})

target_link_libraries(encrypt CURL::libcurl)