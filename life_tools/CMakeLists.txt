add_library(life_tools STATIC
  life_core.c
  life_io.c
  life_utils.c
)

target_include_directories(life_tools PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}
)

target_link_libraries(life_tools
  m
  log.c
)
