#include <stdio.h>
#include <stdlib.h>
#define MAX_CITIES 51

typedef struct City *CityPointer;
typedef struct City {
	int count;						// how many conneted cities

	int cities[MAX_CITIES];			// connected cities
} City;

typedef struct Cell *CellPointer;

typedef struct CellItem {
  City *city;
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

int main(int argc, char const *argv[]) {
	City cities[MAX_CITIES];
	int cityCount, bridgeCount;
	int x, y;
	int i;

	scanf("%d %d", &cityCount, &bridgeCount);

	i = bridgeCount;
	while(i) {
		cities[x-1].cities[cities[x-1].count] = y-1;
		cities[x-1].count++;

		i--;
	}

	i = bridgeCount;
	while(i) {
		// if has rank 1, do_queue
		i--;
	}
	return 0;
}

void init_queue(Queue *queue) {
  queue->first = (CellPointer) malloc(sizeof(Cell));
  queue->last = queue->first;
  queue->first->next = NULL;
} 

int is_queue_empty(Queue queue) { 
  return (queue.first == queue.last);
} 

void do_queue(CellItem item, Queue *queue) {
  queue->last->next = (CellPointer) malloc(sizeof(Cell));
  queue->last = queue->last->next;
  queue->last->item = item;
  queue->last->next = NULL;
} 

void undo_queue(Queue *queue, CellItem *item) {
  CellPointer pointer;
  if (is_queue_empty(*queue)) { printf("Erro fila esta vazia\n"); return; }
  pointer = queue->first;
  queue->first = queue->first->next;
  *item = queue->first->item;
  free(pointer);
}