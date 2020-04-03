/* leins, 17.12.2017 */
#ifndef TREE_H
#define TREE_H
#define MAX_WORD_LEN 30

/* types */
typedef struct tagTREE {
  char *word;
  struct tagTREE *left, *right;
}tree_t;

/* functions */
tree_t *BuildTree(char *fileName);
void PrintTree(tree_t *tree, int level);
void ClearTree(tree_t **tree);
#endif // TREE_H
