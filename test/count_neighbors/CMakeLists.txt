add_executable(count_neighbors_suite
  count_neighbors.c
)

target_link_libraries(count_neighbors_suite
  life_core
  Unity
)

add_test(count_neighbors_tests count_neighbors_suite)
