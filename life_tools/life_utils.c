#include <life_utils.h>

static config_t const one = 1;

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
