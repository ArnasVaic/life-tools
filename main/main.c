#include <stdio.h>
#include <module_a.h>
#include <life_core.h>

int main(void)
{
  u256_t a = lico_init_from_str(
    "    "
    " ## "
    " ## "
    "    "
  );

  char str[100] = "";
  lico_render_to_str(&a, 4, str);
  printf("pretty value of a:\n%s\n", str);

  return 0;
}
