#include <life_core.h>
#include <assert.h>
#include <string.h>
#include <math.h>

const config_t one = 1;

config_t lico_init_from_str(char const * const input) {

  int input_length = strlen(input);
  int config_size = sqrt(input_length);

  // Check if size of configuration is a perfect square
  assert(config_size * config_size == input_length);

  // Check if the configuration fits inside 256-bit integer
  assert(config_size <= 16);

  config_t result = 0;

  for (int i = 0; i < input_length; ++i) {
    char cell_state = input[i];

    // Check if cell state is valid
    assert(
      cell_state == DEAD_CELL_CHARACTER ||
      cell_state == LIVE_CELL_CHARACTER
    );

    if (cell_state == LIVE_CELL_CHARACTER) {
      lico_seti(&result, i);
    }
  }

  return result;
}

inline void lico_seti(config_t * const config, int const index) {
  (*config) |= (one << index);
}

inline bool lico_geti(config_t const * const config, int const index) {
  return ((*config) >> index) & one;
}

void lico_next(
  config_t * const config,
  int const size,
  config_t const * const nb_masks
) {
  for (int i = 0; i < size * size; ++i) {
    // Count the neighbours
    const int neighbour_cnt = lico_count_neighbours(config, i, nb_masks);

  }

}

int lico_count_neighbours(
  config_t const * const config,
  int const index,
  config_t const * const nb_masks
) {
  // use optimal popcount implementation for current config_t size
  return 0;
}

void lico_init_nb_masks(
  config_t * const nb_masks,
  int const size,
  void (*init_mask)(
    config_t * const mask,
    int const size,
    int const index)
) {

  // Use the stack since there won't be too many of them
  for (int row = 0; row < size * size; ++row) {
    for (int col = 0; col < size * size; ++col) {
      int index = row * size + col;
      config_t * const mask = &nb_masks[index];
      init_mask(mask, size, index);
    }
  }
}

void lico_init_klein_nb_mask(
  config_t * const mask,
  int const size,
  int const row,
  int const col
) {
  *mask = 0;
  // How does this work:
  // https://en.wikipedia.org/wiki/Klein_bottle#:~:text=%5B1%5D-,Construction,-%5Bedit%5D
  for (int i = -1; i < 2; ++i) {

    // Neighbour row, wraps around normally
    int nb_row = (size + row + i) % size;

    for (int j = -1; j < 2; ++j) {

      if (i == 0 && j == 0)
        continue;

      // Neighbour column, if it wraps around, reverse nb_row
      int nb_col = (size + col + j) % size;

      if (col + j == -1 || col + j == size) {
        nb_row = size - 1 - nb_row;
      }

      int index = nb_row * size + nb_col;
      *mask |= one << index;
    }
  }
}

void lico_render_to_str(
  config_t const * const config,
  int const size,
  char * const dest
) {

  int write_index = 0;
  for (int row = 0; row < size; ++row) {
    for (int col = 0; col < size; ++col) {

      int index = row * size + col;
      bool cell_state = lico_geti(config, index);

      dest[write_index++] = cell_state > 0
        ? LIVE_CELL_CHARACTER
        : DEAD_CELL_CHARACTER;
    }
    dest[write_index++] = '\n';
  }
}
