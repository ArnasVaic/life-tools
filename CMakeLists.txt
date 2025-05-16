cmake_minimum_required(VERSION 3.11)

project("Life tools" C)

set(TARGET_GROUP release CACHE STRING "Group to build")

add_subdirectory(life_core)

if(TARGET_GROUP STREQUAL release)
    add_subdirectory(main)
elseif(TARGET_GROUP STREQUAL debug)
    add_subdirectory(main)
elseif(TARGET_GROUP STREQUAL test)
    include(CTest)
    add_subdirectory(external)
    add_subdirectory(test)
else()
    message(FATAL_ERROR "Given TARGET_GROUP unknown")
endif()
