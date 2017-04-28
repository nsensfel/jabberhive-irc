cmake_minimum_required(VERSION 3.0 FATAL_ERROR)

project("JabberHive - IRC Gateway")

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake_modules/")

include(FindPkgConfig)
include(FindPkgConfig)

add_subdirectory(src)
add_definitions(-D_POSIX_SOURCE)
add_definitions(-D_POSIX_C_SOURCE=200809L)
find_package(LibIRCClient REQUIRED)

if(CMAKE_COMPILER_IS_GNUCC)
   set(CMAKE_C_FLAGS "-g -Wall -Wpedantic -Wconversion")
   #message(STATUS "GNUCC detected. Adding '-O3' parameter.")
   #set(CMAKE_C_FLAGS "-O3")
endif()

# ${SRC_FILES} is recursively defined in the subdirectories.
# Each subdirectory only adds the source files that are present at its level.
add_executable(jabberhive-irc ${SRC_FILES})
set_property(TARGET jabberhive-irc PROPERTY C_STANDARD 99)
set_property(TARGET jabberhive-irc PROPERTY C_STANDARD_REQUIRED ON)
target_link_libraries(jabberhive-irc ${LibIRCClient_LIBRARIES})

## OPTION HANDLING #############################################################
# TODO
