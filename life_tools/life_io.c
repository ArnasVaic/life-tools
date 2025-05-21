#include <life_io.h>
#include <assert.h>
#include <string.h>
#include <math.h>

static config_t const one = 1;

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

void lico_render_config(
  config_t const * const config,
  int const size,
  char * const dest
) {
  int write_index = 0;

  // Top border
  dest[write_index++] = '+';
  for (int i = 0; i < size * 2; ++i)
    dest[write_index++] = '-';
  dest[write_index++] = '+';
  dest[write_index++] = '\n';

  for (int row = 0; row < size; ++row) {
    dest[write_index++] = '|';
    for (int col = 0; col < size; ++col) {
      int const index = row * size + col;
      bool const cell_state = lico_geti(config, index);

      char ch = cell_state ? LIVE_CELL_CHARACTER : DEAD_CELL_CHARACTER;
      dest[write_index++] = ch;
      dest[write_index++] = ' ';  // double width for 2:1 ratio
    }
    dest[write_index++] = '|';
    dest[write_index++] = '\n';
  }

  // Bottom border
  dest[write_index++] = '+';
  for (int i = 0; i < size * 2; ++i)
    dest[write_index++] = '-';
  dest[write_index++] = '+';
  dest[write_index++] = '\n';

  // Null-terminate
  dest[write_index] = '\0';
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
