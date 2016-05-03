#ifndef CONSTRUCTORS
#define CONSTRUCTORS
#include "structs.c"

Record *create_record(int order);
void *free_record(Record *record);

Page *create_page();
Page *create_internal(int order);
Page *create_leaf(int order);
Pair *create_pair(int key, int value);

#endif
