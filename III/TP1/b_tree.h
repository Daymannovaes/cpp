#ifndef B_TREE
#define B_TREE

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
	int *ids;				// identifier of children files
	int id;					// indentify self file

	PagePointer parent;		// parent page
} Page;

typedef struct Page Tree; 	// only an alias for the root page

#endif