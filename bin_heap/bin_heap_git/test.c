// leins, 10.05.2018

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include "heap.h"
#include "test.h"

/* unit tests
 * for Insert, Delete, Merge, GetMin
*/

heap_t *Build_NullTree()
{
  return NULL;
}
heap_t *Build_1_NodeTree(int d)
{
  heap_t *h = CreateNode(d);

  return h;
}
heap_t *Build_2_NodeTree(int d1, int d2)
{
  heap_t *h = CreateNode(d1);
  heap_t *child = CreateNode(d2);

  h->degree = 1;
  h->child = child;
  child->parent = h;

  return h;
}
heap_t *Build_3_NodeTree(int d1, int d2, int d3)
{
  heap_t *h = CreateNode(d1);
  heap_t *sibling2nodes = Build_2_NodeTree(d2, d3);

  h->sibling = sibling2nodes;
  return h;
}
heap_t *Build_4_NodeTree(int d1, int d2, int d3, int d4)
{
  heap_t *h = CreateNode(d1);
  heap_t *child = Build_2_NodeTree(d2, d3);
  heap_t *chSibling = CreateNode(d4);

  child->sibling = chSibling;
  child->parent = h;
  h->child = child;
  h->degree = 2;

  return h;
}

void Clear_1_NodeTree(heap_t **h)
{
  free(*h);
}
void Clear_2_NodeTree(heap_t **h)
{
  heap_t *tmp = (*h)->child;

  free(tmp);
  tmp = *h;
  free(tmp);
}
void Clear_3_NodeTree(heap_t **h)
{
  heap_t *tmp = *h;

  free(tmp->sibling->child);
  free(tmp->sibling);
  free(tmp);
}
void Clear_4_NodeTree(heap_t **h)
{
  heap_t *tmp = *h;

  free(tmp->child->child);
  free(tmp->child->sibling);
  free(tmp->child);
  free(tmp);
}

bool_t Test_Insert_0()
{
  heap_t *h = Build_NullTree();
  bool_t ans = m_true;
  int data = 50;
  int numOfNodes = 1;

  h = Insert(h, data);

  if (!HeapCheck(h, numOfNodes))
  {
    ans = m_false;
    printf("\tINSERT_TEST: error insert in zero heap\n");
  }
  else
    printf("\tINSERT_TEST: insert in zero heap is ok\n");

  Clear_1_NodeTree(&h);
  return ans;
}
bool_t Test_Insert_1()
{
  heap_t *h = Build_1_NodeTree(1);
  bool_t ans = m_true;
  int data = 50;
  int numOfNodes = 2;

  h = Insert(h, data);

  if (!HeapCheck(h, numOfNodes))
  {
    ans = m_false;
    printf("\tINSERT_TEST: error insert in 1 heap\n");
  }
  else
    printf("\tINSERT_TEST: insert in 1 heap is ok\n");

  Clear_2_NodeTree(&h);
  return ans;
}
bool_t Test_Insert_2()
{
  heap_t *h = Build_2_NodeTree(8, 10);
  bool_t ans = m_true;
  int data = 50;
  int numOfNodes = 3;

  h = Insert(h, data);

  if (!HeapCheck(h, numOfNodes))
  {
    ans = m_false;
    printf("\tINSERT_TEST: error insert in 2 heap\n");
  }
  else
    printf("\tINSERT_TEST: insert in 2 heap is ok\n");

  Clear_3_NodeTree(&h);
  return ans;
}
bool_t Test_Insert_3()
{
  heap_t *h = Build_3_NodeTree(8, 16, 32);
  bool_t ans = m_true;
  int data = 50;
  int numOfNodes = 4;

  h = Insert(h, data);

  if (!HeapCheck(h, numOfNodes))
  {
    ans = m_false;
    printf("\tINSERT_TEST: error insert in 3 heap\n");
  }
  else
    printf("\tINSERT_TEST: insert in 3 heap is ok\n");

  Clear_4_NodeTree(&h);
  return ans;
}
bool_t Test_Insert()
{
  bool_t ans = m_true;

  if (!Test_Insert_0())
    ans = m_false;
  if (!Test_Insert_1())
    ans = m_false;
  if (!Test_Insert_2())
    ans = m_false;
  if (!Test_Insert_3())
    ans = m_false;
  return ans;
} /* end of function */

bool_t Test_Del_0()
{
  heap_t *h = Build_NullTree();
  bool_t ans = m_true;
  int data = 50;

  h = Delete(h, data);

  if (!h)
  {
    ans = m_false;
    printf("\tDELETE_TEST: error delete from zero heap\n");
  }
  else
    printf("\tDELETE_TEST: delete from zero heap is ok\n");

  return ans;
}
bool_t Test_Del_1()
{
  heap_t *h = Build_1_NodeTree(1);
  bool_t ans = m_true;
  int data = 1;
  int numOfNodes = 0;

  h = Delete(h, data);

  if (!HeapCheck(h, numOfNodes))
  {
    ans = m_false;
    printf("\tDELETE_TEST: error delete from 1 heap\n");
    Clear_1_NodeTree(&h);
  }
  else
    printf("\tDELETE_TEST: delete from 1 heap is ok\n");

  return ans;
}
bool_t Test_Del_2()
{
  heap_t *h = Build_2_NodeTree(8, 10);
  bool_t ans = m_true;
  int data = 10;
  int numOfNodes = 1;

  h = Delete(h, data);

  if (!HeapCheck(h, numOfNodes))
  {
    ans = m_false;
    printf("\tDELETE_TEST: error delete from 2 heap\n");
  }
  else
    printf("\tDELETE_TEST: delete from 2 heap is ok\n");

  Clear_1_NodeTree(&h);
  return ans;
}
bool_t Test_Del_3()
{
  heap_t *h = Build_3_NodeTree(1, 2, 3);
  bool_t ans = m_true;
  int data = 3;
  int numOfNodes = 2;

  h = Delete(h, data);

  if (!HeapCheck(h, numOfNodes))
  {
    ans = m_false;
    printf("\tDELETE_TEST: error delete from 3 heap\n");
  }
  else
    printf("\tDELETE_TEST: delete from 3 heap is ok\n");

  Clear_2_NodeTree(&h);
  return ans;
}
bool_t Test_Del_4()
{
  heap_t *h = Build_4_NodeTree(1, 8, 10, 90);
  bool_t ans = m_true;
  int data = 10;
  int numOfNodes = 3;

  h = Delete(h, data);

  if (!HeapCheck(h, numOfNodes))
  {
    ans = m_false;
    printf("\tDELETE_TEST: error delete from 4 heap\n");
  }
  else
    printf("\tDELETE_TEST: delete from 4 heap is ok\n");

  Clear_3_NodeTree(&h);
  return ans;
}
bool_t Test_Delete()
{
  bool_t ans = m_true;

  if (!Test_Del_0())
    ans = m_false;
  if (!Test_Del_1())
    ans = m_false;
  if (!Test_Del_2())
    ans = m_false;
  if (!Test_Del_3())
    ans = m_false;
  if (!Test_Del_4())
    ans = m_false;
  return ans;

} /* end of function */


bool_t Test_Merge_0_0()
{
  heap_t *h1 = Build_NullTree();
  heap_t *h2 = Build_NullTree();
  bool_t ans = m_true;
  int numOfNodes = 0;

  h1 = Merge(h1, h2);

  if (!HeapCheck(h1, numOfNodes))
  {
    ans = m_false;
    printf("\tMERGE_TEST: error merge 0 & 0 heaps\n");
  }
  else
    printf("\tMERGE_TEST: merge 0 & 0 heaps is ok\n");

  return ans;
}
bool_t Test_Merge_1_0()
{
  heap_t *h1 = Build_NullTree();
  heap_t *h2 = Build_1_NodeTree(1);
  bool_t ans = m_true;
  int numOfNodes = 1;

  h1 = Merge(h1, h2);

  if (!HeapCheck(h1, numOfNodes))
  {
    ans = m_false;
    printf("\tMERGE_TEST: error merge 1 & 0 heaps\n");
  }
  else
    printf("\tMERGE_TEST: merge 1 & 0 heaps is ok\n");

  Clear_1_NodeTree(&h1);

  return ans;
}
bool_t Test_Merge_2_2()
{
  heap_t *h1 = Build_2_NodeTree(8, 10);
  heap_t *h2 = Build_2_NodeTree(16, 18);
  bool_t ans = m_true;
  int numOfNodes = 4;

  h1 = Merge(h1, h2);

  if (!HeapCheck(h1, numOfNodes))
  {
    ans = m_false;
    printf("\tMERGE_TEST: error merge 2 & 0 heaps\n");
  }
  else
    printf("\tMERGE_TEST: merge 1 & 0 heaps is ok\n");

  Clear_4_NodeTree(&h1);
  return ans;
}
bool_t Test_Merge_1_3()
{
  heap_t *h1 = Build_1_NodeTree(1);
  heap_t *h2 = Build_3_NodeTree(8, 33, 99);
  bool_t ans = m_true;
  int numOfNodes = 4;

  h1 = Merge(h1, h2);

  if (!HeapCheck(h1, numOfNodes))
  {
    ans = m_false;
    printf("\tMERGE_TEST: error merge 1 & 3 heaps\n");
  }
  else
    printf("\tMERGE_TEST: merge 1 & 3 heaps is ok\n");

  Clear_4_NodeTree(&h1);
  return ans;
}

bool_t Test_Merge()
{
  bool_t ans = m_true;

  if (!Test_Merge_0_0())
    ans = m_false;
  if (!Test_Merge_1_0())
    ans = m_false;
  if (!Test_Merge_2_2())
    ans = m_false;
  if (!Test_Merge_1_3())
    ans = m_false;
  return ans;

} /* end of function */

bool_t Test_GetMin_1()
{
  heap_t *h1 = Build_1_NodeTree(1);
  heap_t *h2, *h;
  bool_t ans = m_true;
  int numOfNodes = 0;

  h2 = GetMin(&h1, &h);

  if (!HeapCheck(h, numOfNodes) || h2->data != 1)
  {
    ans = m_false;
    printf("\tGETMIN_TEST: error get min from 1 heap\n");
  }
  else
    printf("\tGETMIN_TEST: get min from 1 heap is ok\n");

  free(h2);
  return ans;
}
bool_t Test_GetMin_2()
{
  heap_t *h1 = Build_2_NodeTree(1, 10);
  heap_t *h2, *h;
  bool_t ans = m_true;
  int numOfNodes = 1;

  h2 = GetMin(&h1, &h);

  if (!HeapCheck(h, numOfNodes) || h2->data != 1)
  {
    ans = m_false;
    printf("\tGETMIN_TEST: error get min from 2 heap\n");
  }
  else
    printf("\tGETMIN_TEST: get min from 2 heap is ok\n");

  free(h2);
  Clear_1_NodeTree(&h);
  return ans;
}
bool_t Test_GetMin_3()
{
  heap_t *h1 = Build_3_NodeTree(29, 1, 10);
  heap_t *h2, *h;
  bool_t ans = m_true;
  int numOfNodes = 2;

  h2 = GetMin(&h1, &h);

  if (!HeapCheck(h, numOfNodes) || h2->data != 1)
  {
    ans = m_false;
    printf("\tGETMIN_TEST: error get min from 3 heap\n");
  }
  else
    printf("\tGETMIN_TEST: get min from 3 heap is ok\n");

  free(h2);
  Clear_2_NodeTree(&h);
  return ans;
}
bool_t Test_GetMin_4()
{
  heap_t *h1 = Build_4_NodeTree(1, 10, 20, 100);
  heap_t *h2, *h;
  bool_t ans = m_true;
  int numOfNodes = 3;

  h2 = GetMin(&h1, &h);

  if (!HeapCheck(h, numOfNodes) || h2->data != 1)
  {
    ans = m_false;
    printf("\tGETMIN_TEST: error get min from 4 heap\n");
  }
  else
    printf("\tGETMIN_TEST: get min from 4 heap is ok\n");

  free(h2);
  Clear_3_NodeTree(&h);
  return ans;
}

bool_t Test_GetMin()
{
  bool_t ans = m_true;

  if (!Test_GetMin_1())
    ans = m_false;
  if (!Test_GetMin_2())
    ans = m_false;
  if (!Test_GetMin_3())
    ans = m_false;
  if (!Test_GetMin_4())
    ans = m_false;
  return ans;

} /* end of function */

/* not unit tests
*/

int GetC(uint m, uint n)
{
  uint *A = malloc(sizeof(uint) * (n+1));
  uint res = 1;
  bool_t error = m_false;

  // odz check
  if (n == 1 || m == n + 1)
    res = m;
  else if (n > m)
    res = 0;
  else if (n == m)
    res = 1;
  else
  {
    if (n > m - n)
      n = m - n;
    if (m > n + 1)
    {
      for (uint i = 0; i <= n; i++) // initialization
        A[i] = 1;

      for (uint i = 1; i <= m - n; i++)
      {
        for (uint j = 1; j <= n; j++)
        {
          if (A[j] > UINT_MAX - A[j - 1]) // memory check
          {
            error = m_true;
            break;
          }
          A[j] = A[j] + A[j - 1];
        }

        if (error)
          break;
      }

      res = A[n];
    }
  }
  free(A);
  return res;
}

static int NumOfNodes(heap_t *heap, bool_t clear)
{
  static int cnt;

  if (clear)
  {
    cnt = 0;
  }
  if (heap == NULL)
    return 0;
  if (heap->child == NULL && heap->sibling == NULL)
    return ++cnt;
  else
  {
    NumOfNodes(heap->child, m_false);
    NumOfNodes(heap->sibling, m_false);
    cnt++;
    return cnt;
  }
} // end of func

static int numOfParents(heap_t *heap)
{
  int n = 0;

  while (heap->parent != NULL)
  {
    heap = heap->parent;
    n++;
  }

  return n;
}

static void CountDegrees(heap_t *heap, int *a)
{
  if (heap == NULL)
    return;
  else
  {
    int n = numOfParents(heap);
    a[n]++;
    CountDegrees(heap->child, a);
    if (n != 0)
      CountDegrees(heap->sibling, a);
  }
} //

static bool_t CheckLevelsNodes(heap_t *heap)
{
  if (heap != NULL)
  {
    int rDeg = heap->degree;
    int *a = malloc(sizeof(int) * (rDeg + 1));
    bool_t ans = m_true;

    for (int i = 0; i < rDeg + 1; i++)
      a[i] = 0;

    CountDegrees(heap, a);

    for (int i = 0; i < rDeg + 1; i++)
      if (a[i] != GetC(rDeg, i))
      {
        printf("checkLevelsNodes: ERROR (incorrect binary tree - root %i)\n", heap->data);
        break;
      }

    printf("checkLevelsNodes: CORRECT\n");
    free(a);
    return ans;
  }
  return m_true;
} // end of function

// checking root property
static bool_t HeapListCheck(heap_t *heap)
{ 
  bool_t ans = m_true;

  if (heap != NULL)
  {
    int n = NumOfNodes(heap, m_true);
    int maxDeg = 0;
    int nChild = NumOfNodes(heap->child, m_true);
    heap_t *last = NULL;

    while (heap != NULL)
    {
      nChild = NumOfNodes(heap->child, m_true);
      if (pow(2, heap->degree) != nChild + 1)
        printf("heap_list_check: ERROR (not correct nodes quantity in tree with root %i)\n", heap->data);
      else
        printf("heap_list_check: CORRECT (correct nodes quantity)\n");

      if (heap->sibling != NULL)
      {
        if (heap->sibling->degree <= heap->degree)
          ans = m_false;
      }
      else
        last = heap;
      CheckLevelsNodes(heap);
      heap = heap->sibling;
    }

    maxDeg = log(n) / log(2);
    heap = last;

    if (heap->degree != maxDeg) // maxDeg = log(2, n)
      printf("heap_list_check: ERROR (max degree is wrong, %i != %i)\n", heap->degree, maxDeg);
    else
      printf("heap_list_check: CORRECT (max degree is correct - %i)\n", maxDeg);
  }
  return ans;
} // end of func

heap_t *LoadHeap(char *fileName, int *cnt)
{
  FILE *f;
  heap_t *heap = NULL;

  if ((f = fopen(fileName, "r")) == NULL)
    printf("cnnot open %s file\n", fileName);
  else
  {
    int n;
    int tmp = 0;

    fscanf(f, "%i", cnt);

    while (tmp++ < *cnt)
    {
      if (fscanf(f, "%i", &n))
        heap = Insert(heap, n);
    }
    fclose(f);
    return heap;
  }

  return NULL;
} // end of function

static int NumOfChild(heap_t *heap)
{
  int cnt = 0;

  while (heap->child != NULL)
  {
    heap = heap->child;
    cnt++;
  }
  return cnt;
} // end of function

bool_t CheckLoadHeap(heap_t *heap)
{
  static bool_t ans = m_true;

  if (heap == NULL || ans == m_false)
    return ans;
  else
  {
    /* all tests here */
    if (heap->parent != NULL && heap->parent->data >= heap->data)
    {
      printf("CheckLoadHeap: %i - parent has bigger or the same data \n", heap->data);
      ans = m_false;
    }

    if (heap->degree != NumOfChild(heap))
    {
      printf("CheckLoadHeap: incorrect degree in node %i - \n", heap->data);
      ans = m_false;
    }

    CheckLoadHeap(heap->child);
    CheckLoadHeap(heap->sibling);
    return ans;
  }
} /* end of function */

// check properties of every heap list - (???)
bool_t HeapCheck(heap_t *heap, int numOfNodes)
{
  bool_t ans = m_true;
  int n = NumOfNodes(heap, m_true);

  if (numOfNodes == n)
  {
    printf("NumOfNodes: CORRECT (size = %i)\n", n);
    if (HeapListCheck(heap))
    {
      printf("HeapListCheck: CORRECT (root list is ok)\n");
      ans = CheckLoadHeap(heap);
      if (ans)
        printf("CheckLoadHeap: CORRECT (degrees - ok, all parents have less size)\n");
    }
    else
    {
      printf("HeapListCheck: ERROR");
      ans = m_false;
    }
  }
  else
  {
    if (n > numOfNodes)
      printf("NumOfNodes: ERROR (too much nodes)\n");
    else
      printf("NumOfNodes: ERROR (less nodes)\n");
    ans = m_false;
  }

  return ans;
} // end of func
