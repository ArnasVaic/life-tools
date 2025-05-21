#ifndef LIFE_UTILS_H
#define LIFE_UTILS_H

#include <life_core.h>

// Initialize neighbour count masks.
void lico_init_nb_masks(
  config_t * const nb_masks,
  int const size,
  void (*wrap_coordinate)(
    int row,
    int col,
    int size,
    int * const new_row,
    int * const new_col
  )
);

// Initialize neighbour count mask for Klein bottle topology.
void lico_init_mask(
  config_t * const mask,
  int size,
  int row,
  int col,
  void (*wrap_coordinate)(
    int row,
    int col,
    int size,
    int * const new_row,
    int * const new_col)
);

// Wrap given coordinate assuming a Klein-bottle topology
void lico_wrap_klein(
  int row,
  int col,
  int size,
  int *const new_row,
  int *const new_col
);

#endif // LIFE_UTILS_H
