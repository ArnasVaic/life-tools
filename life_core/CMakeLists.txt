add_library(life_core STATIC
    module_a.c
)

target_include_directories(life_core PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
)
