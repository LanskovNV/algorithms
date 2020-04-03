/* leins, 01.05.2018 */

#include <stdio.h>
#include "test.h"

#define START_INSERT_TESTS
#define START_DELETE_TESTS
#define START_MERGE_TESTS
#define START_GETMIN_TESTS

int main()
{ 
#ifdef START_INSERT_TESTS
  Test_Insert();
#endif

#ifdef START_DELETE_TESTS
  Test_Delete();
#endif

#ifdef START_MERGE_TESTS
  Test_Merge();
#endif

#ifdef START_GETMIN_TESTS
  Test_GetMin();
#endif


  return 0;
}
