cmake_minimum_required(VERSION 3.12)
project(learn_depth_clustering)

set(CMAKE_CXX_STANDARD 14)
#set(CMAKE_INCLUDE_CURRENT_DIR ON)
#include_directories(communication)

add_subdirectory(communication)

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} identifiable)