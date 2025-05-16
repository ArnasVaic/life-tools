#include <life_core.h>
#include <assert.h>
#include <string.h>
#include <math.h>

const u256_t one = 1;

u256_t lico_init_from_str(char const * const input) {

  int input_length = strlen(input);
  int config_size = sqrt(input_length);

  // Check if size of configuration is a perfect square
  assert(config_size * config_size == input_length);

  // Check if the configuration fits inside 256-bit integer
  assert(config_size <= 16);

  u256_t result = 0;

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

inline void lico_seti(u256_t * const config, int index) {
  (*config) |= (one << index);
}

inline bool lico_geti(u256_t const * const config, int index) {
  return ((*config) >> index) & one;
}

void next_klein(u256_t * const config) {

}

void lico_render_to_str(
  u256_t const * const config,
  int size,
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
