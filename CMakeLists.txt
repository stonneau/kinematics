cmake_minimum_required(VERSION 2.6)
project(kinematics)


set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/build/")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin/")

add_subdirectory (src/tests/kinematics)

