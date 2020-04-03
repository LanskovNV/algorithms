#include <stdio.h>
#include "bloom.h"
#include "test.h"

 #define TEST_HASH
 #define TEST_CONTAINS
 #define TEST_INSERT

int main(void)
{
#ifdef TEST_HASH
  if (Test_MyHash())
    printf("TEST_MY_HASH: PASSED\n");
#endif

#ifdef TEST_CONTAINS
  if (Test_Contains())
    printf("TEST_CONTAINS: PASSED\n");
#endif

#ifdef TEST_INSERT
  if (Test_Insert())
    printf("TEST_INSERT: PASSED\n");

#endif

}
