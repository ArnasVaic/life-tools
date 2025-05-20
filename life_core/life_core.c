#include <life_core.h>
#include <assert.h>
#include <string.h>
#include <math.h>

const config_t one = 1;

config_t lico_init_from_str(char const * const input) {

  int const input_length = strlen(input);
  int const config_size = sqrt(input_length);

  // Check if size of configuration is a perfect square
  assert(config_size * config_size == input_length);

  // Check if the configuration fits inside 256-bit integer
  assert(config_size <= 16);

  config_t result = 0;

  for (int i = 0; i < input_length; ++i) {
    char const cell_state = input[i];

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
    int const neighbour_cnt = lico_count_neighbors(config, i, nb_masks);

  }
}

inline int lico_coord_to_index(int row, int col, int size) {
  return row * size + col;
}

inline int lico_count_neighbors(
  config_t const * const config,
  int const index,
  config_t const * const nb_masks
) {
  config_t const masked = *config & nb_masks[index];

  // When Clang 21 comes out, this will require a single call
  // https://clang.llvm.org/docs/LanguageExtensions.html#builtin-popcountg

#if CONFIG_BITS == 128

  int const part1 = __builtin_popcountll((unsigned long long)masked);
  int const part2 = __builtin_popcountll((unsigned long long)(masked >> 64));
  return part1 + part2;

#endif

  // Provide separate implementation for other bitsizes

  return 0;
}

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
) {
  for (int row = 0; row < size; ++row) {
    for (int col = 0; col < size; ++col) {
      int const index = row * size + col;
      config_t * const mask = &nb_masks[index];
      lico_init_mask(mask, size, row, col, wrap_coordinate);
    }
  }
}

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
) {
  *mask = 0;

  for (int dr = -1; dr < 2; ++dr) {
    for (int dc = -1; dc < 2; ++dc) {
      if (dr == 0 && dc == 0)
        continue;

      int wrapped_row, wrapped_col;
      wrap_coordinate(row + dr, col + dc, size, &wrapped_row, &wrapped_col);

      // Wrapped coordinates will always be non-negative
      if (wrapped_row == -1 || wrapped_col == -1) {
        continue; // Do not mark neighbour at all
      }

      int const index = wrapped_row * size + wrapped_col;
      *mask |= one << index;
    }
  }
}

void lico_render_config(
  config_t const * const config,
  int const size,
  char * const dest
) {

  int write_index = 0;
  for (int row = 0; row < size; ++row) {
    for (int col = 0; col < size; ++col) {

      int const index = row * size + col;
      bool const cell_state = lico_geti(config, index);

      dest[write_index++] = cell_state > 0
        ? LIVE_CELL_CHARACTER
        : DEAD_CELL_CHARACTER;
    }
    dest[write_index++] = '\n';
  }
}

void lico_render_bits(
  config_t const * const config,
  int const size,
  char * const dest
) {
  int write_index = 0;
  dest[write_index++] = '0';
  dest[write_index++] = 'b';
  for (int i = 0; i < size * size; ++i) {
    bool const bit = ((*config) >> i) & one;
    dest[write_index++] = bit ? '1' : '0';
  }
}

void lico_wrap_klein(
  int row,
  int col,
  int size,
  int *const new_row,
  int *const new_col
) {
  // Why this works:
  // https://en.wikipedia.org/wiki/Klein_bottle#:~:text=%5B1%5D-,Construction,-%5Bedit%5D

  // Wrap columns normally
  *new_col = (col % size + size) % size;

  // Wrap rows, but flip column on wrap
  int const wrapped_row = (row % size + size) % size;
  int const vertical_wraps = (row - wrapped_row) / size;

  // Flip the column on each vertical wrap
  if (vertical_wraps % 2 != 0) {
    *new_col = size - 1 - *new_col;
  }

  *new_row = wrapped_row;
}
