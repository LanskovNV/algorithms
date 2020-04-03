/* leins, 02.12.2017 */
#ifndef SEARCH_H
#define SEARCH_H
#include <stdio.h>
/* types 2.0 */
typedef enum {
  fals,
  tru
}bool_t;
struct tagCHILDREN;
typedef struct tagLIST {
  int data;
  int numOfChildren;
  bool_t isVisited;
  struct tagLIST *next;
  struct tagCHILDREN *children;
}list_t;
typedef struct tagCHILDREN{
  int data;
  list_t *ptr;
  struct tagCHILDREN *next;
}children_t;
typedef struct tagSTACK {
  list_t *elem;
  struct tagSTACK *next;
}stack_t;
/* functions */
int BuildTree(FILE *stream, list_t **new);
bool_t Search(list_t *list, int endVal, bool_t ret);
void ClearList(list_t **list);
bool_t Search_2_0(list_t *list, int endVal);
#endif // SOURCE_H
