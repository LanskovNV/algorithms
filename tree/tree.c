/* leins, 17.12.2017 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"

static char *GetWord(FILE *stream)
{
  char c;
  char *word = malloc(MAX_WORD_LEN + 1);
  int i = 0;

  if (word == NULL)
    return NULL;
  while ((c = fgetc(stream)) != '(' && c != ')' && i < MAX_WORD_LEN)
  {
    if (c == EOF || c == ')')
    {
      free(word);
      return NULL;
    }
    word[i++] = c;
  }
  if (i >= MAX_WORD_LEN)
  {
    free(word);
    return NULL;
  }
  if (c == '(' || c == ')')
    ungetc(c, stream);
  word[i] = '\0';
  return word;
} /* end of function */
tree_t *CreateList(char *word)
{
  tree_t *tree = malloc(sizeof(tree_t));

  if (tree == NULL)
    return NULL;
  tree->word = word;
  tree->left = NULL;
  tree->right = NULL;

  return tree;
} /* end of function */
static tree_t *CreateTree(FILE *stream)
{
  tree_t *tree = NULL;
  char *word = GetWord(stream);

  if (word == NULL || !strcmp(word, ""))
  {
    free(word);
    return NULL;
  }

  tree = CreateList(word);
  if (getc(stream) == '(')
  {
    tree->left = CreateTree(stream);
    getc(stream);
  }
  if (getc(stream) == '(')
  {
    tree->right = CreateTree(stream);
    getc(stream);
  }

  return tree;
} /* end of file */

tree_t *BuildTree(char *fileName)
{
  FILE *stream;
  tree_t *tree = NULL;

  // opening file
  if ((stream = fopen(fileName, "r")) == NULL)
    return NULL;

  tree = CreateTree(stream);

  // finish
  fclose(stream);
  return tree;
} /* end of function */

void PrintTree(tree_t *tree, int level)
{
  int i;

  if (tree == NULL)
    return;
  if (tree->right != NULL)
    PrintTree(tree->right, level + 1);
  for (i = 0; i < level; i++)
    printf("\t");
  printf("%s\n", tree->word);
  if (tree->left != NULL)
    PrintTree(tree->left, level + 1);
} /* end of function */

void ClearTree(tree_t **tree)
{
  if (*tree == NULL)
    return;
  if ((*tree)->left != NULL)
     ClearTree(&(*tree)->left);
  if ((*tree)->right != NULL)
     ClearTree(&(*tree)->right);
  if ((*tree)->right == NULL && (*tree)->left == NULL)
  {
    free((*tree)->word);
    free(*tree);
    *tree = NULL;
  }
} /* end of function */

