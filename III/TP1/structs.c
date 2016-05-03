#include "structs.h"
#define MAX_BUFF 64

typedef char Field[MAX_BUFF];		// field is a string
typedef struct Record {
	int key;
	int count;				// number of fields in this record
	Field *fields;			// each record has many fields
} Record;
typedef struct Pair {
	int key;				// record key
	int value;				// row number of the record;
} Pair;

typedef struct Page *PagePointer;

typedef struct Page {
	int isLeaf;

	int count;				// number of keys in this page
	Pair *data;				// array of keys/values
	PagePointer *pointers;	// array of pages

	PagePointer parent;		// parent page
} Page;

typedef struct Page Tree; 	// only an alias for the root page