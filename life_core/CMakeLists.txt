add_library(life_core STATIC
  module_a.c
  life_core.c
)

target_include_directories(life_core PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}
)

target_link_libraries(life_core
  m
)
