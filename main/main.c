#include <stdio.h>
#include <life_tools.h>
#include <string.h>

int main(void)
{
  const int size = 5;
  config_t curr = lico_init_from_str(
    "..O.."
    "O.O.."
    ".OO.."
    "....."
    "....."
  );
  config_t next = 0;

  config_t nb_masks[size * size];
  memset(nb_masks, 0, size * size * sizeof(config_t));

  lico_init_nb_masks(nb_masks, size, lico_wrap_klein);

  char str[200] = "";

  for (int i = 0; i < 20; ++i) {
    lico_next(
      &curr,
      &next,
      size,
      nb_masks,
      GOL_RULESET
    );

    lico_render_config(&next, size, str);
    printf("Iteration [%d]:\n%s", i, str);
    memset(str, 0, 100);
    curr = next;
  }
  return 0;
}
