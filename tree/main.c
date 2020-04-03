/* leins, 17.12.2017 */
#include <stdio.h>
#include "tree.h"
int main(void)
{
  tree_t *tree = BuildTree("input.txt");

  PrintTree(tree, 0);
  ClearTree(&tree);
  return 0;
}
