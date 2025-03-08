project("Sample Project" C)
cmake_minimum_required(VERSION 3.0)

set(TARGET_GROUP release CACHE STRING "Group to build")

# Set output directories based on TARGET_GROUP
if(TARGET_GROUP STREQUAL release)
    set(OUTPUT_DIR ${CMAKE_BINARY_DIR}/bin/release)
elseif(TARGET_GROUP STREQUAL debug)
    set(OUTPUT_DIR ${CMAKE_BINARY_DIR}/bin/debug)
elseif(TARGET_GROUP STREQUAL test)
    set(OUTPUT_DIR ${CMAKE_BINARY_DIR}/bin/test)
else()
    message(FATAL_ERROR "Given TARGET_GROUP unknown")
endif()

# Ensure the directory exists
file(MAKE_DIRECTORY ${OUTPUT_DIR})

# Apply to executables and libraries
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${OUTPUT_DIR})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${OUTPUT_DIR})

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
