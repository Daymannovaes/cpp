#include <stdio.h>
#include <stdlib.h>

typedef struct Cell *pointerCell;

typedef struct Cell {
  int number;
  pointerCell next, previous;
} TCell;

typedef struct{
  pointerCell first, last;
} TList;

int isEmpty(TList *list);
void insert(TList *list, int number);
void removeFromList(TList *list, int number);
void moveBiggest(TList *list);
pointerCell createCell(int number);

int main() {
  int queue, pqueue, stack;
  int rows, number;
  int command;
  int i;

  TList list;
  list.first = malloc(sizeof(TCell));
  
  list.first->number = 0; // real values are always positive
  
  list.first->next = NULL;
  list.last = list.first;

  while(scanf("%d", &rows) != EOF) {
    queue  = 1;
    pqueue = 1;
    stack  = 1;

    for(i=0; i<rows; i++) {
      scanf("%d %d", &command, &number);

      if(command == 1) {
        insert(&list, number);
      }

      else if(command == 2) {
        // defining types
        queue = (number != list.first->next->number) ? 0 : queue;
        pqueue = (number != list.first->number) ? 0 : pqueue;
        stack = (number != list.last->number) ? 0 : stack;

        removeFromList(&list, number);
      }
    }

    // clear list
    list.first->next = NULL;
    list.first->number = 0;

    // print type
    if(!queue && !pqueue && !stack)
      printf("impossible");

    else if(queue && !pqueue && !stack)
      printf("queue");

    else if(!queue && pqueue && !stack)
      printf("priority queue");

    else if(!queue && !pqueue && stack)
      printf("stack");

    else
      printf("not sure");

    printf("\n");
  }

  return 0;
}
int isEmpty(TList *list) {
  return list->first->next == NULL;
}

pointerCell createCell(int number) {
  pointerCell cell = malloc(sizeof(TCell));
  cell->number = number;
  cell->next = NULL;
}

void insert(TList *list, int number) {
  pointerCell cell = createCell(number);

  // if number is the lower, insert in the beginning
  if(number > list->first->number)
    list->first->number = number;

  if(isEmpty(list)) {
    list->first->next = cell;
    list->last = cell;
    cell->previous = list->first;
  }
  else {
    list->last->next = cell;
    cell->previous = list->last;
    list->last = cell;
  }
}

void moveBiggest(TList *list) {
  pointerCell pointer;
  int number = 0;

  pointer = list->first->next;

  while(pointer != NULL){
    if(number < pointer->number)
      number = pointer->number;

    pointer = pointer->next;
  }
  
  list->first->number = number;
}

void removeFromList(TList *list, int number) {
  pointerCell cell;

  cell = list->first->next;

  while(cell != NULL) {
    if(cell->number == number) {
      if(cell == list->last) {
        cell->previous->next = NULL;
        list->last = cell->previous;  

        moveBiggest(list);
        free(cell);
        return;
      }
      else {
        cell->previous->next = cell->next;
        cell->next->previous = cell->previous;

        moveBiggest(list);
        free(cell);
        return;
      }
    }
    cell = cell->next;
  }
}