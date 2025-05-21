#ifndef LIFE_IO_H
#define LIFE_IO_H

#include <life_core.h>

#define DEAD_CELL_CHARACTER '.'
#define LIVE_CELL_CHARACTER 'O'

// Parse configuration from a string. Size of configuration
// will be inferred from number of characters. Method will fail
// if number of characters in input is not a perfect square.
// Input characters shall only be either DEAD_CELL_CHARACTER or LIVE_CELL_CHARACTER.
config_t lico_init_from_str(char const * const str);

// Render configuration to a string
void lico_render_config(
  config_t const * const config,
  int size,
  char * const dest
);

// Render configuration bits to a string
void lico_render_bits(
  config_t const * const config,
  int size,
  char * const dest
);

// Render configuration as a hexadecimal number.
void lico_render_hex(
  config_t config,
  char * const dest
);

#endif // LIFE_IO_H
