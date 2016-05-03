#include "constructors.h"
#include <stdlib.h>
#include <stdbool.h>

Record *create_record(int order) {
	Record *record;
	record = malloc(sizeof(Record));

	record->count = 0;
	record->fields = malloc(order * sizeof(Field));

	return record;
}
void *free_record(Record *record) {
	free(record->fields);
	free(record);
}

Page *create_page() {
	Page *page;
	page = malloc(sizeof(Page));

	page->count  = 0;
	page->data = NULL;
	page->pointers = NULL;
	page->parent = NULL;

	return page;
}
Page *create_leaf(int order) {
	Page *page = create_page();
	page->isLeaf = true;

	page->data = malloc(order * sizeof(Pair));

	return page;
}
Page *create_internal(int order) {
	Page *page = create_leaf(order);
	page->isLeaf = false;

	page->pointers = malloc((order+1) * sizeof(PagePointer));

	return page;
}
Pair *create_pair(int key, int value) {
	Pair *pair;
	pair = malloc(sizeof(Pair));

	pair->key = key;
	pair->value = value;

	return pair;
}
