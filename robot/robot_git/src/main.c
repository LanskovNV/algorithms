/* leins, 08.03.2018 */
#include <stdio.h>
#include "robot.h"

int main(void)
{
  int x0, y0, k;
  FILE *stream;
  char *fileName = "input.txt"; // default input file

  if ((stream = fopen(fileName, "r")) == NULL)
  {
    printf("cannot open input file\n");
  }
  else
  {
    // no check for correct input!!!
    fscanf(stream, "%i", &x0);
    fscanf(stream, "%i", &y0);
    fscanf(stream, "%i", &k);
    fclose(stream);

    // output results
    printf("num of ways - %i\n", GetNumOfWays(x0, y0, k));
  }

  return 0;
} /* end of main */
