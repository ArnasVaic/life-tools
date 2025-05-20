#include <unity.h>

#include <life_core.h>

const int size = 5;
config_t nb_masks[size * size];
config_t filled;

void test_lico_count_klein_neighbors_should_return_the_same_count_anywhere(void)
{
  for (int i = 0; i < size * size; ++i) {
    int nb_cnt = lico_count_neighbors(&filled, i, nb_masks);
    TEST_ASSERT_EQUAL_INT32(8, nb_cnt);
  }
}

int main(void)
{
  UNITY_BEGIN();

  // Initialize common fields
  lico_init_nb_masks(nb_masks, size, lico_wrap_klein);

  filled = lico_init_from_str(
    "#####"
    "#####"
    "#####"
    "#####"
    "#####"
  );

  RUN_TEST(test_lico_count_klein_neighbors_should_return_the_same_count_anywhere);

  return UNITY_END();
}
