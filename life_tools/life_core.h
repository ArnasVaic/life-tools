#ifndef LIFE_CORE_H
#define LIFE_CORE_H

#define CONFIG_BITS 128

// This library uses an unsigned _BitInt to represent a finite
// game of life configuration at a specific moment in time
typedef __uint128_t config_t;

// Game of life ruleset.
#define GOL_RULESET 0b000001100000001000

// Set configuration cell value by index
void lico_seti(config_t * const config, int index);

// Set configuration cell value by index
void lico_set(config_t * const config, int index, bool state);

// Get configuration cell value by index
config_t lico_geti(config_t const * const config, int index);

// Iterate configuration according to a given ruleset.
void lico_next(
  config_t const * restrict current,
  config_t * restrict next,
  int size,
  config_t const * restrict nb_masks,
  int ruleset
);

// Retrieve the next state for a cell by
// neighbor count for the current ruleset.
int lico_get_next_cell_state(config_t cell_state, int neighbor_count, int ruleset);

// Convert row column pair to index.
int lico_coord_to_index(int row, int col, int size);

// Count live neighbors of a cell
// located at index in a given configuration.
int lico_count_neighbors(
  config_t const * restrict config,
  int index,
  config_t const * restrict nb_masks
);

// Find a repeating pattern given some initial configuration.
// Returns the index to the first configuration in the loop.
int lico_find_repeating(
  config_t initial,
  int const size,
  config_t const * restrict nb_masks,
  int ruleset,
  config_t * restrict visited,
  int visited_capacity,
  int *loop_length
);

#endif // LIFE_CORE_H
