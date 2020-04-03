/* leins, 02.12.2017 */
#include <stdio.h>
#include <stdlib.h>
#include "search.h"

static void AddChild(children_t **elem, int data)
{
  children_t *new = malloc(sizeof(children_t));

  if (new == NULL)
    return;
  new->data = data;
  new->next = NULL;
  new->ptr = NULL;
  while (*elem != NULL)
    elem = &(*elem)->next;
  *elem = new;
} /* end of function */

static list_t *CreateList(int data, int numOfChildren)
{
  list_t *new = malloc(sizeof(list_t));

  if (new == NULL)
    return NULL;
  new->data = data;
  new->numOfChildren = numOfChildren;
  new->next = NULL;
  new->children = NULL;
  new->isVisited = fals;
  return new;
} /* end of function */

list_t *GetList(list_t *list, int data)
{
  while (list != NULL)
  {
    if (list->data == data)
      return list;
    list = list->next;
  }
  return NULL;
}
int BuildTree(FILE *stream, list_t **new)
{
  int numOfPeaks = 0, i;
  list_t **list = NULL, *begin = NULL;

  if (stream == NULL)
    return 0;

  fscanf(stream, "%i", &numOfPeaks);
  if (numOfPeaks <= 0)
  {
    printf("no peaks in graph\n");
    return 0;
  }

  for (i = 0; i < numOfPeaks; i++)
  {
    int newData, j;
    int numOfChildren;

    fscanf(stream, "%i", &newData);
    fgetc(stream);
    fscanf(stream, "%i", &numOfChildren);
    *new = CreateList(newData, numOfChildren);
    if (i == 0)
      list = new;
    for (j = 0; j < numOfChildren; j++)
    {
      int newChData;

      fscanf(stream, "%i", &newChData);
      fgetc(stream);
      AddChild(&(*new)->children, newChData);
    }
    new = &(*new)->next;
  }
  begin = *list;
  while (*list != NULL)
  {
    children_t *tmp = (*list)->children;
    while (tmp != NULL)
    {
      tmp->ptr = GetList(begin, tmp->data);
      tmp = tmp->next;
    }
    list = &(*list)->next;
  }
 return numOfPeaks;
} /* end of function */

bool_t Search(list_t *list, int endVal, bool_t ret)
{
  children_t *tmp = NULL;

  list->isVisited = tru;
  if (list == NULL || ret == tru)
    return ret;
  if (list->data == endVal)
  {
    ret = tru;
    return ret;
  }
  tmp = list->children;
  while (tmp != NULL && !ret)
  {
    if (!tmp->ptr->isVisited)
      ret = Search(tmp->ptr, endVal, ret);
    tmp = tmp->next;
  }
  return ret;
} /* end of function */
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
void Push(stack_t **stack, list_t *elem)
{
  if (*stack == NULL)
  {
    *stack = CreateStackElem();
    (*stack)->elem = elem;
    (*stack)->next = NULL;
  }
  else
  {
    stack_t *new = CreateStackElem();

    new->elem = elem;
    new->next = *stack;
    *stack = new;
  }
} /* end of function */

list_t *Pop(stack_t **stack)
{
  if (*stack == NULL)
    return NULL;
  else
  {
    list_t *ret = (*stack)->elem;
    FreeStackElem(stack);
    return ret;
  }
} /* end of function */

bool_t IsWay(list_t *elem)
{
  if (elem == NULL)
    return fals;
  else
  {
    bool_t ret = fals;
    children_t *tmp = elem->children;
    while (tmp != NULL)
    {
      if (!tmp->ptr->isVisited)
      {
        ret = tru;
        break;
      }
      tmp = tmp->next;
    }
    return ret;
  }
}

bool_t Search_2_0(list_t *list, int endVal)
{
  stack_t *stack = NULL;
  bool_t retVal = fals, go = tru;
  list_t *tmp = list;

  while (!retVal && go)
  {
    while (IsWay(tmp) || !tmp->isVisited)
    {
      children_t *tmpChildren = tmp->children;
      tmp->isVisited = tru;

      Push(&stack, tmp);
      if (tmp->data == endVal)
      {
        retVal = tru;
        break;
      }
      while (tmpChildren != NULL)
      {
        if (tmpChildren->ptr->isVisited)
          tmpChildren = tmpChildren->next;
        else
        {
          tmp = tmpChildren->ptr;
          break;
        }
      }
    }
    if (!retVal)
      tmp = Pop(&stack);
    go = IsWay(list);
  }
  while (stack != NULL)
    FreeStackElem(&stack);
  return retVal;
} /* end of function */

static void ClearChildren(children_t **elem)
{
  if (*elem != NULL)
    ClearChildren(&(*elem)->next);
  else
    return;
  free(*elem);
  *elem = NULL;
} /* end of function */

void ClearList(list_t **list)
{
  if (*list != NULL)
    ClearList(&(*list)->next);
  else
    return;
  ClearChildren(&((*list)->children));
  free(*list);
  *list = NULL;
} /* end of function */
