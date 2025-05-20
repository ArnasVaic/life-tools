#ifndef LIFE_CORE_H
#define LIFE_CORE_H

#define CONFIG_BITS 128

// This library uses an unsigned _BitInt to represent a finite
// game of life configuration at a specific moment in time
typedef __uint128_t config_t;

#define DEAD_CELL_CHARACTER ' '
#define LIVE_CELL_CHARACTER '#'

// Parse configuration from a string. Size of configuration
// will be inferred from number of characters. Method will fail
// if number of characters in input is not a perfect square.
config_t lico_init_from_str(char const * const str);

// Set configuration cell value by index
void lico_seti(config_t * const config, int const index);

// Get configuration cell value by index
bool lico_geti(config_t const * const config, int const index);

// Iterate configuration according to the rules of game of life.
void lico_next(
  config_t * const config,
  int const size,
  config_t const * const nb_masks
);

// Convert row column pair to index
int lico_coord_to_index(int row, int col, int size);

// Count live neighbours of a cell
// located at index in a given configuration.
int lico_count_neighbors(
  config_t const * const config,
  int const index,
  config_t const * const nb_masks
);

// Initialize neighbour count masks.
void lico_init_nb_masks(
  config_t * const nb_masks,
  int const size,
  void (*wrap_coordinate)(
    int const row,
    int const col,
    int const size,
    int * const new_row,
    int * const new_col
  )
);

// Initialize neighbour count mask for Klein bottle topology.
void lico_init_mask(
  config_t * const mask,
  int const size,
  int const row,
  int const col,
  void (*wrap_coordinate)(
    int const row,
    int const col,
    int const size,
    int * const new_row,
    int * const new_col)
);

// Render configuration to a string
void lico_render_config(
  config_t const * const config,
  int const size,
  char * const dest
);

// Render configuration bits to a string
void lico_render_bits(
  config_t const * const config,
  int const size,
  char * const dest
);

// Wrap given coordinate assuming a Klein-bottle topology
void lico_wrap_klein(
  int row,
  int col,
  int size,
  int *const new_row,
  int *const new_col
);

#endif // LIFE_CORE_H
