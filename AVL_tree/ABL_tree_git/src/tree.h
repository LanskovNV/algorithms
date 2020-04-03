#ifndef TREE_H
#define TREE_H
/* leins, 26.03.2018 */

typedef unsigned char uchar;

/* ABL-tree type */
typedef struct tagNODE {
  int key;                // key value
  uchar heigth;           // sub-tree heigth
  struct tagNODE *left;
  struct tagNODE *right;
}node_t;

/* functions */
int FindNode(node_t *p, int key);        // interface
node_t *AddNode(node_t *p, int key);     // interface
node_t *DelNode(node_t *p, int k);       // interface
void ClearTree(node_t **tree);           // source
void PrintTree(node_t *tree, int level); // external interface

#endif // TREE_H
