#include <life_core.h>

static config_t const one = 1;

inline void lico_seti(config_t * const config, int const index) {
  (*config) |= (one << index);
}

inline config_t lico_geti(config_t const * const config, int const index) {
  return ((*config) >> index) & one;
}

inline void lico_set(config_t * const config, int const index, bool state) {
  *config ^= (-state) & (one << index);
}

inline void lico_next(
  config_t const * restrict current,
  config_t * restrict next,
  int size,
  config_t const * restrict nb_masks,
  int const ruleset
) {
  *next = 0;
  for (int i = 0; i < size * size; ++i) {
    config_t const current_state = lico_geti(current, i);
    int const nb_cnt = lico_count_neighbors(current, i, nb_masks);
    int const state = lico_get_next_cell_state(current_state, nb_cnt, ruleset);
    lico_set(next, i, state);
  }
}

inline int lico_get_next_cell_state(config_t cell_state, int neighbor_count, int ruleset) {
  return (ruleset >> (neighbor_count + cell_state * 9)) & 1;
}

inline int lico_coord_to_index(int row, int col, int size) {
  return row * size + col;
}

inline int lico_count_neighbors(
  config_t const * restrict config,
  int const index,
  config_t const * restrict nb_masks
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
