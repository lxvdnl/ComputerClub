cmake_minimum_required(VERSION 3.10)
project(ComputerClub)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_DIR src)

set(SOURCES
    ${SOURCE_DIR}/main.cpp
    ${SOURCE_DIR}/Time.hpp
    ${SOURCE_DIR}/Time.cpp
    ${SOURCE_DIR}/Table.hpp
    ${SOURCE_DIR}/Table.cpp
    ${SOURCE_DIR}/ComputerClubHandler.cpp
    ${SOURCE_DIR}/ComputerClubHandler.hpp
)

add_executable(ComputerClub ${SOURCES})
