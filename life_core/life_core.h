#ifndef LIFE_CORE_H
#define LIFE_CORE_H

// This library uses an unsigned 256-bit integer to represent
// a finite game of life configuration at a specific moment in time
typedef unsigned _BitInt(256) u256_t;

#define DEAD_CELL_CHARACTER ' '
#define LIVE_CELL_CHARACTER '#'

// Parse configuration from a string. Size of configuration
// will be inferred from number of characters. Method will fail
// if number of characters in input is not a perfect square.
u256_t lico_init_from_str(char const * const str);

// Set configuration cell value by index
void lico_seti(u256_t * const config, int index);

// Get configuration cell value by index
bool lico_geti(u256_t const * const config, int index);

// Iterate configuration according to the rules of game of life.
// Additionaly, assume the grid wraps around itself in a way
// such that the space is topologically identical to a Klein bottle.
void next_klein(u256_t * const config);

// Render configuration to a string
void lico_render_to_str(
  u256_t const * const config,
  int size,
  char * const dest
);

#endif // LIFE_CORE_H
