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

// Count live neighbours of a cell
// located at index in a given configuration.
int lico_count_neighbours(
  config_t const * const config,
  int const index,
  config_t const * const nb_masks
);

// Initialize neighbour count masks.
void lico_init_nb_masks(
  config_t * const nb_masks,
  int const size,
  void (*init_mask)(
    config_t * const mask,
    int const size,
    int const index)
);

// Initialize neighbour count mask for Klein bottle topology.
void lico_init_klein_nb_mask(
  config_t * const mask,
  int const size,
  int const row,
  int const col
);

// Render configuration to a string
void lico_render_to_str(
  config_t const * const config,
  int const size,
  char * const dest
);

#endif // LIFE_CORE_H
