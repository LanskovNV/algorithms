#pragma once
#ifndef TEST_H
#define TEST_H
// leins, 10.05.2018

#include "heap.h"

typedef enum
{
  m_false,
  m_true
} bool_t;

bool_t HeapCheck(heap_t *heap, int numOfNodes);
heap_t *LoadHeap(char *fileName, int *cnt);


/* unit tests */
bool_t Test_Insert();
bool_t Test_Delete();
bool_t Test_Merge();
bool_t Test_GetMin();

#endif
