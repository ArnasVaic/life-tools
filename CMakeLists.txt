project("Sample Project" C)
cmake_minimum_required(VERSION 3.0)

set(TARGET_GROUP release CACHE STRING "Group to build")

add_subdirectory(module_a)

if(TARGET_GROUP STREQUAL release)
    add_subdirectory(main)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/release)

elseif(TARGET_GROUP STREQUAL debug)
    add_subdirectory(main)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/debug)

elseif(TARGET_GROUP STREQUAL test)
    include(CTest)

    add_subdirectory(external)
    add_subdirectory(test)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/test)
else()
    message(FATAL_ERROR "Given TARGET_GROUP unknown")
endif()
