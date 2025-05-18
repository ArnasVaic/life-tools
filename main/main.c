#include <stdio.h>
#include <module_a.h>
#include <life_core.h>

int main(void)
{
  config_t a = 0;

  lico_init_klein_nb_mask(&a, 5, 0, 0);

  char str[100] = "";
  lico_render_to_str(&a, 4, str);
  printf("pretty value of a:\n%s\n", str);

  return 0;
}
