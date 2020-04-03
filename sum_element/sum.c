/* leins, 13.12.2017 */
#include <stdio.h>
#include <stdlib.h>
#include "sum.h"
/*
 * stack functions
*/
stack_t *CreateStackElem()
{
  return malloc(sizeof(stack_t));
}
void FreeStackElem(stack_t **stack)
{
  stack_t *tmp = *stack;

  *stack = (*stack)->next;
  free(tmp);
  tmp = NULL;
}
void Push(stack_t **stack, int data, int j, int i)
{
  if (*stack == NULL)
  {
    *stack = CreateStackElem();
    (*stack)->sum = data;
    (*stack)->numElem = j;
    (*stack)->i = i;
    (*stack)->next = NULL;
  }
  else
  {
    stack_t *new = CreateStackElem();

    new->sum = (*stack)->sum + data;
    new->next = *stack;
    new->numElem = j;
    new->i= i;
    *stack = new;
  }
} /* end of function */

stack_t *Pop(stack_t **stack)
{
  if (*stack == NULL)
    return NULL;
  else
  {
    stack_t *ret = *stack;
    FreeStackElem(stack);
    return ret;
  }
} /* end of function */
int Compare(const void *a, const void *b)
{
  return *(int*)a - *(int*)b;
} /* end of function */

stack_t *FindSum(int *elements, int sum, int numOfElements)
{
  int i, j = 0;
  stack_t *stack = NULL;

  // sort elements and remove too big
  qsort(elements, numOfElements, sizeof(int), Compare);
  for (i = 0; i < numOfElements; i++)
    if (elements[i] >= sum)
    {
      numOfElements = i + 1;
      break;
    }

  // sorting
  i = 0;
  while (i < numOfElements)
  {
    do
    {
      // choosing next elem to push
      if (stack == NULL)
        j = i;
      else
        j = stack->numElem;
      if (j < numOfElements)
        Push(&stack, elements[j], j + 1, j);
      if (stack->sum == sum)
        break;
      if (j >= numOfElements || stack->sum > sum)
      {
        Pop(&stack);
        if (stack != NULL)
          stack->numElem += 1;
      }
    } while (stack != NULL);

    if (stack != NULL)
      if (stack->sum == sum)
        break;
    i++;
  }

  return stack;
} /* end of function */

