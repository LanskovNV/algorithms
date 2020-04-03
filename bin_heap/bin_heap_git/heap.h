#pragma once
#ifndef HEAP_H
#define HEAP_H

/* binomial heap type */
typedef struct tagHeap
{
  int data;
  int degree;
  struct tagHeap *sibling;
  struct tagHeap *child;
  struct tagHeap *parent;
}heap_t;

/* interface functions */
heap_t *Insert(heap_t *heap,int newData);
heap_t *GetMin(heap_t **heap, heap_t **newH);
heap_t *Merge(heap_t *a, heap_t *b);
heap_t *Delete(heap_t *heap, int data);
void Clear(heap_t **heap);

/* test functions */
heap_t *CreateNode(int data);

#endif
