/* leins, 13.12.2018 */
#include <stdio.h>
#include <stdlib.h>
#include "sum.h"

int main(void)
{
  FILE *stream;
  char *fileName = "input.txt";
  int *elements, sum, numOfElements, i;
  stack_t *stack, *tmp;
  // open file
  if ((stream = fopen(fileName, "r")) == NULL)
  {
    printf("can not open %s file\n", fileName);
    return 0;
  }

  // read data
  fscanf(stream, "%i", &sum);
  fscanf(stream, "%i", &numOfElements);

  if ((elements = malloc(sizeof(int) * numOfElements)) == NULL)
  {
    printf("no memory for source data\n");
    return 0;
  }
  for (i = 0; i < numOfElements; i++)
    fscanf(stream, "%i", &elements[i]);
  fclose(stream);

  stack = FindSum(elements, sum, numOfElements);
  tmp = stack;
  if ((stream = fopen("output.txt", "w")) == NULL)
    printf("cannot open output.txt file");
  if (tmp == NULL)
    fprintf(stream, "0\n");
  while (tmp != NULL)
  {
    fprintf(stream, "%i ", elements[tmp->i]);
    tmp = tmp->next;
  }
  fclose(stream);
  while (stack != NULL)
    FreeStackElem(&stack);
  free(elements);
  return 0;
}
