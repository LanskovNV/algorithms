#ifndef TEST_H
#define TEST_H
/* leins, 17.06.2018 */

#include "bloom.h"

// void Load(bloom_filter_t *bf, char *fileName);
void CheckZeroValues(bloom_filter_t *bf, char *fileName);

/* unit tests */
bool_t Test_MyHash();
bool_t Test_Insert();
bool_t Test_Contains();
#endif // TEST_H
