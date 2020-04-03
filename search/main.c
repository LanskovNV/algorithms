/* leins, 01.12.2017 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "search.h"

int main(void)
{
  FILE *stream;
  char *fileName = "alone.txt";
  list_t *list, *begin = NULL;
  int A, B;

  // show lost byte
  //malloc(1);
  if ((stream = fopen(fileName, "r")) == NULL)
    return 1;

  if (!BuildTree(stream, &list))
    return 1;
  begin = list;
  fscanf(stream, "%i", &A);
  fscanf(stream, "%i", &B);
  while (list != NULL && list->data != A)
    list = list->next;
  if (list == NULL)
    printf("no way from %i to %i\n", A, B);
  else
  {
    if (Search_2_0(list, B)) //if (Search(list, B, fals))
      printf("the way exists\n");
    else
      printf("no such way\n");
  }
  ClearList(&begin);
  fclose(stream);
  return 0;
} /* end of main */
