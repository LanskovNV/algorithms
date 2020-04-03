/* leins, 01.05.2018 */
#include <stdio.h>
#include <stdlib.h>
#include "heap.h"

/*******************
 *  source functions
*******************/

heap_t *CreateNode(int data)
{
  heap_t *newHeap = malloc(sizeof(heap_t));

  if (newHeap == NULL)
    printf("no memory\n");
  else
  {
    newHeap->data = data;
    newHeap->degree = 0;
    newHeap->child = NULL;
    newHeap->sibling = NULL;
    newHeap->parent = NULL;
  }

  return newHeap;
}

static void s_Swap(heap_t **a, heap_t **b)
{
  heap_t *tmp = *a;
  heap_t *bSib = (*b)->sibling;
  heap_t *aSib = *a;

  *a = *b;
  *b = tmp;
  (*a)->sibling = aSib;
  (*b)->sibling = bSib;
}

static void s_SwapData(int *a, int *b)
{
  int tmp = *a;

  *a = *b;
  *b = tmp;
}

static heap_t *s_AddNewSibling(heap_t *heap, heap_t *sibling)
{
  if (heap == NULL)
    heap = sibling;
  else
  {
    heap->sibling = sibling;
    heap = heap->sibling;
  }
  return heap;
}

static heap_t *s_MergeHeapList(heap_t *a, heap_t *b)
{
  heap_t *first = a->degree < b->degree ? a : b;
  heap_t *ans = NULL;

  while (a != NULL && b != NULL)
  {
    if (a->degree < b->degree)
    {
      ans = s_AddNewSibling(ans, a);
      a = a->sibling;
    }
    else
    {
      ans = s_AddNewSibling(ans, b);
      b = b->sibling;
    }

  }

  if (a == NULL)
    ans->sibling = b;
  else
    ans->sibling = a;

  ans = first;

  return ans;
}

static heap_t *s_Connect(heap_t *a, heap_t *b)
{
  heap_t *tmpChild, *tmpSibling;

  if (b->data < a->data)
    s_Swap(&a, &b);

  tmpSibling = b->sibling;
  tmpChild = a->child;
  a->child = b;
  a->child->parent = a;
  a->child->sibling = tmpChild;
  a->sibling = tmpSibling;
  a->degree++;

  return a;
}

static heap_t *s_FixParents(heap_t *heap)
{
  heap_t *first = heap;

  while (heap != NULL)
  {
    heap->parent = NULL;
    heap = heap->sibling;
  }
  return first;
}

static heap_t *s_Reverse(heap_t **heap)
{
  heap_t *firstHeap = *heap, *firstAns = NULL;
  heap_t *ans = NULL;

  if (*heap != NULL)
  {
    while ((*heap)->sibling != NULL)
    {
      while ((*heap)->sibling != NULL)
        heap = &(*heap)->sibling;

      if (firstAns == NULL)
      {
        ans = *heap;
        firstAns = ans;
      }
      else
      {
        ans->sibling = *heap;
        ans = ans->sibling;
      }
      ans->sibling = NULL;
      *heap = NULL;
      heap = &firstHeap;
    }
    if (ans != NULL)
      ans->sibling = *heap;
  }

  return firstAns == NULL ? *heap : firstAns;
}

int s_FindMin(heap_t *heap)
{
  int min = heap->data;

  while(heap != NULL)
  {
    if (heap->data < min)
      min = heap->data;
    heap = heap->sibling;
  }

  return min;
}


heap_t *s_Find(heap_t *heap, int data)
{
  if (heap == NULL)
    return NULL;
  else
  {
    heap_t *ans = NULL;

    if (heap->data == data)
      ans = heap;
    else
    {
      if (heap->data < data && ans == NULL)
        ans = s_Find(heap->child, data);
      if (ans == NULL)
        ans = s_Find(heap->sibling, data);
    }
    return ans;
  }
}

static heap_t *s_Decrease(heap_t *heap, int data)
{
  heap_t *first = heap;
  int min = s_FindMin(heap);

  heap = s_Find(heap, data);
  if (heap != NULL)
  {
    heap->data = min - 1; // crash if min is smallest int!
    while (heap->parent != NULL)
    {
      s_SwapData(&heap->data, &heap->parent->data);
      heap = heap->parent;
    }
    return first;
  }
  else
    return NULL;
}

/**********************
 *  interface functions
**********************/

heap_t *Merge(heap_t *a, heap_t *b)
{
  if (a == NULL)
    return b;
  else if (b == NULL)
    return a;
  else
  {
    heap_t *first = NULL;
    heap_t *ans = s_MergeHeapList(a, b);

    while (ans->sibling != NULL)
    {
      if (ans->degree == ans->sibling->degree)
        ans = s_Connect(ans, ans->sibling);
      else if (ans->degree > ans->sibling->degree)
        s_Swap(&ans, &ans->sibling);
      else
      {
        if (first == NULL)
          first = ans;
        ans = ans->sibling;
      }
    }

    return first == NULL ? ans : first;
  }
}

heap_t *GetMin(heap_t **heap, heap_t **newH)
{
  if (*heap == NULL)
    return NULL;
  else if ((*heap)->sibling == NULL && (*heap)->child == NULL)
  {
    heap_t *ans = *heap;
    *newH = NULL;
    return ans;
  }
  else
  {
    heap_t *toDel = *heap;
    heap_t *delPrew = NULL;
    heap_t *prew = *heap;
    heap_t *first = *heap;
    heap_t *tmp;

    while (*heap != NULL)
    {
      if ((*heap)->data < toDel->data)
      {
        toDel = *heap;
        delPrew = prew;
      }
      prew = *heap;
      heap = &(*heap)->sibling;
    }

    if (delPrew != NULL)
      delPrew->sibling = toDel->sibling;
    else
      first = first->sibling;

    tmp = s_FixParents(toDel->child);
    *newH = Merge(first, s_Reverse(&tmp));

    return toDel;
  }
}

heap_t *Insert(heap_t *heap,int newData)
{
  heap_t *newHeap = CreateNode(newData);

  return Merge(heap, newHeap);
}

heap_t *Delete(heap_t *heap, int data)
{
  heap_t *ans = s_Find(heap, data);
  heap_t *first, *min;

  if (ans != NULL)
  {
    heap = s_Decrease(heap, data);
    min = GetMin(&heap, &first);

    free(min);
    min = NULL;
  }

  return first;
}

void Clear(heap_t **heap)
{
  while(*heap != NULL)
  {
    heap_t *min, *first;

    min = GetMin(heap, &first);
    *heap = first;

    free(min);
    min = NULL;
  }
}
