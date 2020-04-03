/* leins, 13.12.2017 */
#ifndef SUM_H
#define SUM_H

/* types */
typedef struct tagSTACK {
  int i; // номер элемента в массиве всех, не меняется после добавления
  int numElem; // номер следующего элемента для добавления в стэк
               // (остальные уже проверены), меняется --//--
  int sum;     // текущая сумма элементов в стеке
  struct tagSTACK *next;
}stack_t;

/* fuctions */
stack_t *FindSum(int *elements, int sum, int numOfElements);
void FreeStackElem(stack_t **stack);
#endif // SUM_H
