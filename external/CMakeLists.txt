add_library(Unity STATIC Unity/src/unity.c)

target_include_directories(Unity PUBLIC Unity/src)

add_library(log.c STATIC log.c/src/log.c)

target_include_directories(log.c PUBLIC log.c/src)

target_compile_definitions(log.c PUBLIC LOG_USE_COLOR)
