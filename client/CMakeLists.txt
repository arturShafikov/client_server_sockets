cmake_minimum_required(VERSION 3.10)

project(client)

include_directories(include)

file(GLOB SOURCES "src/*.cpp")

add_executable(client ${SOURCES})
