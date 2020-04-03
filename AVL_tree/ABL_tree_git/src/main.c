/* leins, 26.03.2018 */
#include <stdio.h>
#include <stdlib.h>
#include "tree.h"

int main(void)
{
  int run = 1;
  node_t *tree = NULL;
  int key = 0;

  while(run)
  {
    printf("input your command (H - for help):\n");
    switch(getchar())
    {
    case 'H':
      printf("Q - out\n"
             "H - help\n"
             "P - print tree\n"
             "N - add node\n"
             "D - delete node\n"
             "F - find node by key\n");
      break;
    case 'Q':
      run = 0;
      break;
    case 'P':
      PrintTree(tree, 0);
      break;
    case 'N':
      printf("input new key:\n");
      scanf("%i", &key);
      tree = AddNode(tree, key);
      break;
    case 'D':
      printf("input key to del:\n");
      scanf("%i", &key);
      tree = DelNode(tree, key);
      break;
    case 'F':
      printf("input key to find:\n");
      scanf("%i", &key);
      if (FindNode(tree, key))
        printf("key exists\n");
      else
        printf("no such key\n");
      break;
    default:
      printf("incorrect choise, please try again\n");
      break;
    }
    getchar();
  }
  ClearTree(&tree);
  return 0;
} // end of main
