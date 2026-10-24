cmake_minimum_required(VERSION 3.10)
project(shell)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)

include_directories(${PROJECT_SOURCE_DIR}/include)
file(GLOB SOURCES ${PROJECT_SOURCE_DIR}/src/*.cpp)
add_executable(${PROJECT_NAME} ${SOURCES})
