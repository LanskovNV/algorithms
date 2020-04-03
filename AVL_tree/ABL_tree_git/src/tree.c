/* leins, 26.03.2018 */
#include <stdio.h>
#include <stdlib.h>
#include "tree.h"

/* ****************
 * source functions
******************/
static node_t *CreateNode(int key) // create list
{
  node_t *new = malloc(sizeof(node_t));

  if (new != NULL)
  {
    new->heigth = 1;
    new->key = key;
    new->left = NULL;
    new->right = NULL;
  }
  return new;
} // end of function

static uchar Heigth(node_t *p) // return heigth of tree (Heigth(NULL) = 0)
{
  return p ? p->heigth : 0;
} // end of function

static int BalanceFactor(node_t *p) //return: {-2, -1, 0, 1, 2}
{
  return p == NULL ? 0 : Heigth(p->right) - Heigth(p->left);
} // end of function

void FixHeigth(node_t **p) // for 1 node
{
  uchar hr, hl;

  if (*p == NULL)
    return;
  hr = Heigth((*p)->right);
  hl = Heigth((*p)->left);
  (*p)->heigth = (hl > hr ? hl : hr) + 1;
} // end of function

node_t *RotateRight(node_t *p)
{
  node_t *q = p->left;

  p->left = q->right;
  q->right = p;
  FixHeigth(&p);
  FixHeigth(&q);
  return q;
} // end of functions

node_t *RotateLeft(node_t *q)
{
  node_t *p = q->right;

  q->right = p->left;
  p->left = q;
  FixHeigth(&q);
  FixHeigth(&p);
  return p;
} // end of functions

static node_t *Balance(node_t *p)
{
  int bFact = BalanceFactor(p);

  FixHeigth(&p);
  if (bFact == 2)
  {
    if (BalanceFactor(p->right) < 0)
      p->right = RotateRight(p->right);
    return RotateLeft(p);
  }
  if (bFact == -2)
  {
    if (BalanceFactor(p->left) > 0)
      p->left = RotateLeft(p->left);
    return RotateRight(p);
  }
  return p;
} // end of function
static node_t *FindMin(node_t *p) // return min elem
{
  return p->left ? FindMin(p->left) : p;
} // end of function
static node_t *RemoveMin(node_t *p)
{
  if (p->left == 0)
    return p->right;
  p->left = RemoveMin(p->left);
  return Balance(p);
} // end of function

/* *******************
 * interface functions
*********************/
void PrintTree(node_t *tree, int level)
{
  int i;

  if (tree == NULL)
    return;
  if (tree->right != NULL)
    PrintTree(tree->right, level + 1);
  for (i = 0; i < level; i++)
    printf("\t");
  printf("%i\n", tree->key);
  if (tree->left != NULL)
    PrintTree(tree->left, level + 1);
} // end of function
node_t *AddNode(node_t *p, int key)
{
  if (p == NULL)
    return CreateNode(key);
  else
  {
    if (key < p->key)
      p->left = AddNode(p->left, key);
    else
      p->right = AddNode(p->right, key);
  }
  return Balance(p);
} // end of function
void ClearTree(node_t **tree)
{
  if (*tree == NULL)
    return;
  if ((*tree)->left != NULL)
     ClearTree(&(*tree)->left);
  if ((*tree)->right != NULL)
     ClearTree(&(*tree)->right);
  if ((*tree)->right == NULL && (*tree)->left == NULL)
  {
    free(*tree);
    *tree = NULL;
  }
} // end of function

node_t *DelNode(node_t *p, int key)
{
  if (p == NULL)
    return NULL;
  else
  {
    if (key < p->key)
      p->left = DelNode(p->left, key);
    else if (key > p->key)
      p->right = DelNode(p->right, key);
    else
    {
      node_t *q = p->left;
      node_t *r = p->right;
      node_t *min = NULL;

      free(p);
      if (r == NULL)
        return q;
      min = FindMin(r);
      min->right = RemoveMin(r);
      min->left = q;
      return Balance(min);
    }
  }
  return Balance(p);
} // end of function

int FindNode(node_t *p, int key)
{
  int ans = 0;

  while (p != NULL)
  {
    if (p->key == key)
    {
      ans = 1;
      break;
    }
    if (key < p->key)
      p = p->left;
    else
      p = p->right;
  }
  return ans;
} // end of function
