#include "b_tree.h"

#ifndef QUEUE
#define QUEUE

typedef struct Cell *CellPointer;

typedef struct CellItem {
  Page *page;
} CellItem;

typedef struct Cell {
  CellItem item;
  CellPointer next;
} Cell;

typedef struct Queue {
  CellPointer first, last;
} Queue;

void init_queue(Queue *queue);
int is_queue_empty(Queue queue);
void do_queue(CellItem x, Queue *queue);
void undo_queue(Queue *queue, CellItem *item);

#endif
