cmake_minimum_required(VERSION 3.14)

project(alele LANGUAGES CXX VERSION 1.0)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/cmake)

# --------------------------------------------------------#
# Compiler settings
# --------------------------------------------------------#

set(CMAKE_CXX_STANDARD 20)

# --------------------------------------------------------#
# Dependencies
# --------------------------------------------------------#

find_package(libzmq 4.3 REQUIRED)
find_package(Threads REQUIRED)


# --------------------------------------------------------#
# Subdirectories
# --------------------------------------------------------#

add_subdirectory(src)
