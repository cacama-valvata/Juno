#include "playerclient.h"

#define BUFSIZE 256
#define INPUTLEN 32

void run_test(char* name, int (*test_func)(void)) 
{
  printf("Running test: %s\n", name);
  if (test_func() == 0)
  {
    printf("  PASS\n");
  } 
  else 
  {
    printf("  FAIL\n");
  }
}

int test_example_1(void)
 {
  int expected = 42;
  int actual = 42;
  return expected == actual ? 0 : 1;
}


int main(void)
{
    run_test("test_example_1", test_example_1);
    return 0;
}