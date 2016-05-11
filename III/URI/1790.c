#include <stdio.h>
#include <stdlib.h>
#define MAX_CITIES 51

typedef struct City *CityPointer;
typedef struct City {
	int id;
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
	Queue rank1_queue;
	CellItem item;
	City cities[MAX_CITIES];
	int cityCount, bridgeCount;
	int x, y;
	int i;
	
	init_queue(&rank1_queue);
	
	for(i=0; i<MAX_CITIES; i++) {
		cities[i].count = 0;
	}

	scanf("%d %d", &cityCount, &bridgeCount);

	i = bridgeCount;
	while(i) {
					cities[x-1].cities[cities[x-1].count] = y-1;
		cities[x-1].id = x-1;
		cities[x-1].count++;
		
cities[y-1].cities[cities[y-1].count] = x-1;
		cities[y-1].id = y-1;
		cities[y-1].count++;

		i--;
	}

	i = bridgeCount;
	while(i) {
		// if has rank 1, do_queue
		if(cities[i].count == 1) {
			item.city = cities[i];
			do_queue(item, &rank1_queue);
		}
		i--;
	}
	
	int idTo;
	while(!is_queue_empty(&rank1_queue)) {
		undo_queue(&rank1_queue, &item);
		cityTo = item.city.cities[0];
		remove_bridge(&cities[idTo], item.city.id);
		if(cities[idTo].count == 1) {
			item.city = cities[idTo];
			do_queue(item, &rank1_queue);
		}
		bridgeCount--;
}
	return 0;
}

void remove_bridge(City *city, int idTo) {
	int doShift = 0;
	int i;
	
	for(i=0; i<city->count; i++) {
		if(doShift)
			city->cities[i-1] = city->cities[i];
		doShift = doShift || (city->cities[i] == idTo);
	}
	
	city->count--;
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