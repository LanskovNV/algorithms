/* leins, 08.03.2018 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "robot.h"

typedef int** table_t;

/*
static void CopyTable(int **a, int **b, int size)
{
  int i, j;

  for (i = 0 ; i < size; i++)
    for (j = 0; j < size; j++)
      a[i][j] = b[i][j];
} // end of function
*/
static void PrintTable(int **a, int size)
{
  int i, j;

  for (i = 0 ; i < size; i++)
  {
    for (j = 0; j< size; j++)
    {
      printf("%i", a[i][j]);

      if (a[i][j] / 10 == 0)
         printf("     ");
      else if (a[i][j] / 100 == 0)
         printf("    ");
      else if (a[i][j] / 1000 == 0)
         printf("   ");
      else if (a[i][j] / 10000 == 0)
         printf("  ");
      else if (a[i][j] / 100000 == 0)
         printf(" ");
    }
    printf("\n");
  }
  printf("\n");
} // end of function
static void Swap(int *a, int *b)
{
  int tmp = *a;
  *a = *b;
  *b = tmp;
}
static int CountWays(int k, int x0, int y0)
{
  int i, j, r,c1 = 0, c2 = 1;
  int size = 2 * k + 1, res = -1;
  int **ways = (int **)malloc(sizeof(int*) * size);
  int **a = (int **)malloc(sizeof(int*) * size);
  table_t mas[2] = {ways, a};

  // no check for malloc !!!
  // initialization
  for (i = 0; i < size; i++)
  {
    ways[i] = (int *)malloc(size * sizeof(int));
    a[i] = (int *)malloc(size * sizeof(int));
  }

  for (i = 0; i < size; i++)
    for (j = 0; j < size; j++)
      a[i][j] = 0;
  a[k][k] = 1;

  for (r = 1; r <= k; r++)
  {
    Swap(&c1, &c2);
    for (i = 0; i < size; i++)
      for (j = 0; j < size; j++)
      {
        int s = 0;

        if(i != size - 1)
          s += mas[c1][i + 1][j]; // ways
        if(i != 0)
          s += mas[c1][i - 1][j];
        if(j != size - 1)
          s += mas[c1][i][j + 1];
        if(j != 0)
          s += mas[c1][i][j - 1];
        mas[c2][i][j] = s; // a
      }
    // PrintTable(mas[c2], size);
  }
  PrintTable(mas[c2], size);

  res = mas[c2][x0 + k][y0 + k];
  // free memory
  for (i = 0; i < size; i++)
  {
    free(ways[i]);
    free(a[i]);
  }
  free(ways);
  free(a);

  return res;
} // end of function
int GetNumOfWays(int x0, int y0, int k)
{
  int result = -1;

  // algoritm:
  if ((x0 + y0 - k) % 2 != 0 || x0 + y0 > k) // odz check
    result = 0;
  else if ((x0 == 0 && k == abs(y0)) || (y0 == 0 && k == abs(x0))) // only 1 way exists
    result = 1;
  else
    result = CountWays(k, x0, y0);

  return result;
} /* end of function */
