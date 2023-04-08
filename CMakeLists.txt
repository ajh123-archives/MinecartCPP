cmake_minimum_required(VERSION 3.11) # FetchContent is available in 3.11+
project(Minecart)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON) # Generate compile_commands.json
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# Dependencies
include(cmake/3rdparty.cmake)

# Our Project
include(cmake/minecart.cmake)
include(cmake/minecart_editor.cmake)
