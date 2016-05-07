#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

#define MAX_BUFF 1024
#define READ_STR "%63s"

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
	int *ids;				// identifier of children files
	int id;					// indentify self file

	PagePointer parent;		// parent page
} Page;

typedef struct Page Tree; 	// only an alias for the root page

// ---- fila


typedef struct TipoCelula *TipoApontador;

typedef Page* TipoChave;

typedef struct TipoItem {
  TipoChave Chave;
  /* outros componentes */
} TipoItem;

typedef struct TipoCelula {
  TipoItem Item;
  TipoApontador Prox;
} TipoCelula;

typedef struct TipoFila {
  TipoApontador Frente, Tras;
} TipoFila;

void FFVazia(TipoFila *Fila)
{ Fila->Frente = (TipoApontador) malloc(sizeof(TipoCelula));
  Fila->Tras = Fila->Frente;
  Fila->Frente->Prox = NULL;
} 

int Vazia(TipoFila Fila)
{ return (Fila.Frente == Fila.Tras); } 

int filaCount;
void Enfileira(TipoItem x, TipoFila *Fila)
{ Fila->Tras->Prox = (TipoApontador) malloc(sizeof(TipoCelula));
  Fila->Tras = Fila->Tras->Prox;
  Fila->Tras->Item = x;
  Fila->Tras->Prox = NULL;
  filaCount++;
} 

void Desenfileira(TipoFila *Fila, TipoItem *Item)
{ TipoApontador q;
  if (Vazia(*Fila)) { printf("Erro fila esta vazia\n"); return; }
  q = Fila->Frente;
  Fila->Frente = Fila->Frente->Prox;
  *Item = Fila->Frente->Item;
  free(q);
  filaCount--;
} 

TipoFila FILA;
// ---- fila


Record *create_record(int order);
void free_record(Record *record);
void free_tree(Tree *tree, Page *page);
void create_page_file(int id, Page *page);
void load_child(Page *page, int index, int order);

void insert_field_in_record(Record *record, Field field);
void read_line_from(FILE *file, char *str);
void remove_new_line(char *str);
Tree *command_add(FILE *output, FILE *input, int order, int fieldCount, int keyNumber, Tree *tree, int recordCount, int *pageCount);
void print_record(Record *record);
void print_page(Page *page);
void print_tree(Tree *tree, int printSelf, int order);

void insert_record_in_file(Record *record, FILE *file);
Tree *insert_record_in_tree(Tree *tree, int key, int value, int *pageCount, int order);
void insert_record_in_leaf(Tree *tree, Page *page, Pair *data, int id, int order);
Tree *split_and_insert_in_leaf(Tree *tree, Page *page, Pair *data, int *pageCount, int order);
Tree *insert_record_in_parent(Tree *tree, Page *left, Page *right, Pair *data, int *pageCount, int order);
void insert_record_in_internal(Page *page, Page *left, Page *right, Pair *data, int *pageCount, int order);
Tree *split_and_insert_in_internal(Tree *tree, Page *leftParent, Page *left, Page *right, Pair *data, int *pageCount, int order);

Page *create_page();
Page *create_internal(int order);
Page *create_leaf(int order);
Pair *create_pair(int key, int value);

void search_and_print_in_file(FILE *output, FILE *input, FILE *record, int order, Tree *tree);
void print_in_file(FILE *output, FILE *record, int row);
void dump(Tree *tree, int order, FILE *output);
void dump_page(Page *page, FILE *output);


int main(int argc, char const *argv[]) {
    setbuf(stdout, NULL);
	FFVazia(&FILA);
	filaCount = 0;

	Tree *tree;

	FILE *output, *input, *record_w, *record_r;
	int order;
	int fieldCount, keyNumber;

	record_w = fopen("records.txt", "w"); // create file
	fclose(record_w);
	output 		= fopen(argv[1], "wb");
	input  		= fopen(argv[2], "r");
	order  		= atoi(argv[3]);
	fieldCount 	= atoi(argv[4]);
	keyNumber 	= atoi(argv[5]);

	tree = create_leaf(order);

	char str[MAX_BUFF];
	int recordCount = 0;
	int pageCount = 0;

	while(!feof(input)) {
		strcpy(str, " ");
		read_line_from(input, str);

		if(strcmp(str, "add") == 0) {
			record_w = fopen("records.txt", "a");
			tree = command_add(record_w, input, order, fieldCount, keyNumber, tree, recordCount, &pageCount);
			recordCount++;
			fclose(record_w);
		}
		if(strcmp(str, "search") == 0) {
			record_r	= fopen("records.txt", "r");
			search_and_print_in_file(output, input, record_r, order, tree);
			fclose(record_r);
		}
		if(strcmp(str, "dump") == 0) {
			dump(tree, order, output);
		}
	}

	int i;
	char fileName[3];
	// for(i=0; i<tree->count+1; i++) {
	// 	printf(" %d ", tree->ids[i]);
	// }
	// print_tree(tree, true, order);
	
	for(i=0; i<pageCount; i++) {
		sprintf(fileName, "%d", i);
		remove(fileName);
	}

	// printf("end");
	return 0;
}

Record *create_record(int order) {
	Record *record;
	record = malloc(sizeof(Record));

	record->count = 0;
	record->fields = malloc(order * sizeof(Field));

	return record;
}
void free_record(Record *record) {
	free(record->fields);
	free(record);
}

void free_tree(Tree *tree, Page *page) {
	while(!Vazia(FILA)) {
		TipoItem item;
		item = FILA.Frente->Prox->Item;
		Desenfileira(&FILA, &item);
		free(item.Chave);
	}
}
void insert_field_in_record(Record *record, Field field) {
	strcpy(record->fields[record->count], field);
	record->count++;
}

void read_line_from(FILE *file, char *str) {
    fscanf(file, READ_STR, str);
    remove_new_line(str);
}
void remove_new_line(char *str) {
    if (str != NULL && str[strlen(str) - 1] == '\n')
        str[strlen(str) - 1] = '\0';
}

Tree *command_add(FILE *output, FILE *input, int order, int fieldCount, int keyNumber, Tree *tree, int recordCount, int *pageCount) {
	int i;

	Record *record = create_record(fieldCount);
	Field field;

	for(i=0; i<fieldCount; i++) {
		read_line_from(input, field);

		if(i == keyNumber)
			record->key = atoi(field);
		else
			insert_field_in_record(record, field);
	}

	insert_record_in_file(record, output);
	return insert_record_in_tree(tree, record->key, recordCount, pageCount, order);
}

void print_record(Record *record) {
	insert_record_in_file(record, stdout);
}
void print_page(Page *page) {
	FILE *file = stdout;
	int i;
	for(i=0; i<page->count; i++) {
		fprintf(file, "(%d|%d) ", page->data[i].key, page->data[i].value);
	}

	// fprintf(file, "\n");
}
void print_tree(Tree *tree, int printSelf, int order) {
	if(printSelf){
		printf("\n\nlevel c(%d)", tree->count);
		print_page(tree);
		printf("\n");
	}

	int i;
	if(tree->pointers != NULL) {
		for(i=0; i<tree->count+1; i++) {
				load_child(tree, i, order);
				print_page(tree->pointers[i]);
			printf(" | ");
		}
		for(i=0; i<tree->count+1; i++) {
			if(!tree->pointers[i]->isLeaf) {
				printf("\nsons of (%d|%d) \n", tree->pointers[i]->data[0].key, tree->pointers[i]->data[0].value);
				print_tree(tree->pointers[i], false, order);
				printf(" | ");
			}
		}
	}

	if(printSelf) free_tree(tree, tree);
}
void insert_record_in_file(Record *record, FILE *file) {
	fprintf(file, "%d", record->key);

	int i;
	for(i=0; i<record->count; i++) {
		fprintf(file, "\t%s", record->fields[i]);
	}

	fprintf(file, "\n");
}
Tree *insert_record_in_tree(Tree *tree, int key, int value, int *pageCount, int order) {
	Pair *data = create_pair(key, value);


	if(tree->isLeaf) {
		if(tree->count < order)
			insert_record_in_leaf(tree, tree, data, order, -1);
		else {
			tree = split_and_insert_in_leaf(tree, tree, data, pageCount, order);
		}
	}
	else {
		if(tree->count == order) {
			Page *left, *right;

			left = tree;

			int splitIndex, i, j;
			splitIndex = order%2 == 0 ? order/2 : order/2 + 1;

			left->count = splitIndex;
			right = create_internal(order);

			for (i = splitIndex+1, j = 0; i < order; i++, j++) {
				right->data[j].key = left->data[i].key;
				right->data[j].value = left->data[i].value;
				right->pointers[j] = left->pointers[i];
				right->ids[j] = left->ids[i];
				right->count++;
			}
			right->pointers[j] = left->pointers[i];
			right->ids[j] = left->ids[i];

			tree = create_internal(order);

			left->parent = tree;
			right->parent = tree;

			if(left->id == -1) {
				left->id = *pageCount;
				(*pageCount)++;
			}
			if(right->id == -1) {
				right->id = *pageCount;
				(*pageCount)++;
			}

			tree->count++;
			tree->data[0].key = left->data[splitIndex].key;
			tree->data[0].value = left->data[splitIndex].value;
			tree->pointers[0] = left;
			tree->pointers[1] = right;
			tree->ids[0] = left->id;
			tree->ids[1] = right->id;

			create_page_file(left->id, left);
			create_page_file(right->id, right);

		  	TipoItem item1, item2;
		  	item1.Chave = left;
			Enfileira(item1, &FILA);
		  	item2.Chave = right;
			Enfileira(item2, &FILA);
		}
		Page *page = tree;
		int index;
		while(!page->isLeaf) {
			index = 0;
			while (index < page->count && page->data[index].key <= data->key)
				index++;

			load_child(page, index, order);
			page = page->pointers[index];
		}
		if(page->count < order)
			insert_record_in_leaf(tree, page, data, index, order);
		else
			tree = split_and_insert_in_leaf(tree, page, data, pageCount, order);
	}

	free(data);
	free_tree(tree, tree);
	return tree;
}

void insert_record_in_leaf(Tree *tree, Page *page, Pair *data, int id, int order) {
	int i, index;

	index = 0;
	while (index < page->count && page->data[index].key < data->key)
		index++;

	for (i = page->count; i > index; i--) {
		page->data[i] = page->data[i - 1];
	}

	page->data[index].key = data->key;
	page->data[index].value = data->value;
	page->count++;

	if(page != tree) {
		create_page_file(page->parent->ids[id], page);
	}
}

void create_page_file(int id, Page *page) {
	char fileName[3]; // max of 999
	FILE *file;
	int i;

	sprintf(fileName, "%d", id);
	file = fopen(fileName, "wb");

	fprintf(file, "%d\n%d\n", page->isLeaf, page->count);

	for (i = 0; i < page->count; i++) {
		fprintf(file, "%d %d ", page->data[i].key, page->data[i].value);
	}

	if(!page->isLeaf) {
		fprintf(file, "\n");
		for (i = 0; i < page->count+1; i++) {
			fprintf(file, "%d ", page->ids[i]);
		}
	}

	fclose(file);
}
void load_child(Page *page, int index, int order) {
	FILE *file;
	char str[3];
	int id = page->ids[index];

	sprintf(str, "%d", id);
	file = fopen(str, "rb");

	Page *child;
	int isLeaf, count;
	
	read_line_from(file, str);
	isLeaf = atoi(str);

	read_line_from(file, str);
	count = atoi(str);

	child = isLeaf ? create_leaf(order) : create_internal(order);
	child->count = count;
	child->id = id;

	int i, key, value;
	for(i=0; i<child->count; i++) {
		read_line_from(file, str); key = atoi(str);
		read_line_from(file, str); value = atoi(str);

		child->data[i].key = key;
		child->data[i].value = value;
	}
	if(!child->isLeaf) {
		for (i = 0; i < child->count+1; i++) {
			read_line_from(file, str); id = atoi(str);
			child->ids[i] = id;
		}
	}

	if(page->pointers == NULL) page->pointers = malloc((order+1) * sizeof(PagePointer));
	page->pointers[index] = child;
	child->parent = page;

  	TipoItem item;
  	item.Chave = child;
	Enfileira(item, &FILA);

	fclose(file);
}

void insert_record_in_internal(Page *page, Page *left, Page *right, Pair *data, int *pageCount, int order) {
	int i, index;
	char str[2];
	FILE *file;

	index = 0;
	while (index < page->count && page->data[index].key < data->key)
		index++;

	for (i = page->count+1; i > index; i--) {
		page->data[i] = page->data[i - 1];
		if(i != index && i != index+1) {
			page->pointers[i] = page->pointers[i - 1];
			page->ids[i] = page->ids[i - 1];
			load_child(page, i, order);
			create_page_file(page->ids[i], page->pointers[i]);
		}
	}

	page->pointers[index] = left;
	page->pointers[index+1] = right;

	if(left->id == -1) {
		left->id = *pageCount;
		(*pageCount)++;
	}
	if(right->id == -1) {
		right->id = *pageCount;
		(*pageCount)++;
	}

	page->ids[index] = left->id;
	page->ids[index+1] = right->id;

	create_page_file(page->ids[index], page->pointers[index]);
	create_page_file(page->ids[index+1], page->pointers[index+1]);

	page->data[index].key = data->key;
	page->data[index].value = data->value;
	page->count++;

	create_page_file(page->id, page);
}

/** 
 * create two new pages from the *page, point this page
 * as parent 
 */
Tree *split_and_insert_in_leaf(Tree *tree, Page *left, Pair *data, int *pageCount, int order) {
	Page *right;
	Pair *auxPairs;
	int index, splitIndex, i, j;

	auxPairs = malloc((order) * sizeof(Pair));

	for (i = 0, j = 0; i < left->count; i++, j++) {
		auxPairs[j].key = left->data[i].key;
		auxPairs[j].value = left->data[i].value;
	}

	splitIndex = order%2 == 0 ? order/2 : order/2 + 1;

	left->count = 0;
	right = create_leaf(order);

	for (i = 0; i < splitIndex; i++) {
		left->data[i].key = auxPairs[i].key;
		left->data[i].value = auxPairs[i].value;
		left->count++;
	}

	for (i = splitIndex, j = 0; i < order; i++, j++) {
		right->data[j].key = auxPairs[i].key;
		right->data[j].value = auxPairs[i].value;
		right->count++;
	}

	free(auxPairs);

	right->parent = left->parent;

	Page *child;
	child = (data->key >= right->data[0].key) ? right : left;

	index = 0;
	while (index < child->count && child->data[index].key < data->key)
		index++;

	for (i = child->count; i > index; i--) {
		child->data[i] = child->data[i - 1];
	}
	child->data[index].key = data->key;
	child->data[index].value = data->value;
	child->count++;

	data->key = right->data[0].key;
	data->value = right->data[0].value;

	return insert_record_in_parent(tree, left, right, data, pageCount, order);
}
Tree *split_and_insert_in_internal(Tree *tree, Page *leftParent, Page *left, Page *right, Pair *data, int *pageCount, int order) {
	Page *rightParent;
	Pair *auxPairs;
	PagePointer *auxPointers;
	int *auxIds;
	int index, splitIndex, i, j;

	auxPairs = malloc((order+1) * sizeof(Pair));
	auxPointers = malloc((order+2) * sizeof(PagePointer));
	auxIds = malloc((order+2) * sizeof(int));

	index = 0;
	while (index < order && leftParent->data[index].key < data->key)
		index++;

	for (i = 0, j = 0; i < leftParent->count; i++, j++) {
		if (j == index) j++;
		auxPointers[j] = leftParent->pointers[i];
	}
	for (i = 0, j = 0; i < leftParent->count; i++, j++) {
		if (j == index) j++;
		auxPairs[j].key = leftParent->data[i].key;
		auxPairs[j].value = leftParent->data[i].value;
	}
	for (i = 0, j = 0; i < leftParent->count+1; i++, j++) {
		auxIds[i] = leftParent->ids[i];
	}

	auxPairs[index].key = data->key;
	auxPairs[index].value = data->value;

	auxPointers[index] = left;
	auxPointers[index+1] = right;

	splitIndex = order%2 == 0 ? order/2 : order/2 + 1;

	leftParent->count = 0;
	rightParent = create_internal(order);

	for (i = 0; i < splitIndex; i++) {
		leftParent->data[i].key = auxPairs[i].key;
		leftParent->data[i].value = auxPairs[i].value;
		leftParent->pointers[i] = auxPointers[i];
		leftParent->ids[i] = auxIds[i];
		leftParent->count++;
	}
	leftParent->pointers[splitIndex] = auxPointers[splitIndex];

	for (i = splitIndex+1, j = 0; i < order+1; i++, j++) {
		rightParent->data[j].key = auxPairs[i].key;
		rightParent->data[j].value = auxPairs[i].value;
		rightParent->pointers[j] = auxPointers[i];
		rightParent->ids[j] = auxIds[i];
		rightParent->count++;
	}
	rightParent->pointers[j] = auxPointers[order+1];

	free(auxPairs);
	free(auxPointers);
	free(auxIds);
	rightParent->parent = leftParent->parent;

	data->key = rightParent->data[0].key;
	data->value = rightParent->data[0].value;

	if(right->id == -1) {
		right->id = *pageCount;
		(*pageCount)++;
	}
	rightParent->ids[j] = right->id;
	create_page_file(left->id, left);
	create_page_file(right->id, right);

	return insert_record_in_parent(tree, leftParent, rightParent, data, pageCount, order);
}

Tree *insert_record_in_parent(Tree *tree, Page *left, Page *right, Pair *data, int *pageCount, int order) {
	Page *parent = left->parent;
	int index;

	// left equals root (tree)
	if(parent == NULL) {
		parent = create_internal(order);
		tree = parent;

		left->parent = tree;
		right->parent = tree;

	  	TipoItem item1, item2;
	  	item1.Chave = left;
		Enfileira(item1, &FILA);
	  	item2.Chave = right;
		Enfileira(item2, &FILA);
	}

	if(parent->count < order)
		insert_record_in_internal(parent, left, right, data, pageCount, order);
	else {
		return split_and_insert_in_internal(tree, parent, left, right, data, pageCount, order);
	}

	return tree;
}

Page *create_page() {
	Page *page;
	page = malloc(sizeof(Page));

	page->count  = 0;
	page->id = -1;
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
	page->ids = malloc((order+1) * sizeof(int));

	return page;
}
Pair *create_pair(int key, int value) {
	Pair *pair;
	pair = malloc(sizeof(Pair));

	pair->key = key;
	pair->value = value;

	return pair;
}

void search_and_print_in_file(FILE *output, FILE *input, FILE *record, int order, Tree *tree) {
	int key;
	char str[MAX_BUFF];

	read_line_from(input, str);
	key = atoi(str);

	Page *page = tree;
	int index;
	index = 0;
	while(!page->isLeaf) {
		while (index < page->count && page->data[index].key <= key)
			index++;

		load_child(page, index, order);
		page = page->pointers[index];
	}

	index = 0;
	while (index < page->count && page->data[index].key != key)
		index++;

	if(index < page->count)
		return print_in_file(output, record, page->data[index].value);
	else {
		fprintf(output, "search\nnull\nsearch\n");
	}

	free_tree(tree, tree);
}
void print_in_file(FILE *output, FILE *record, int row) {
	char str[MAX_BUFF * 2];

	row++;
	while(row) {
		fgets(str, MAX_BUFF * 2, record);
		row--;
	}

	remove_new_line(str);
	fprintf(output, "search\n%s\nsearch\n", str);
}

void dump(Tree *tree, int order, FILE *output) {
	free_tree(tree, tree); // ensure
	TipoItem item, n;
	int i;
  	item.Chave = tree;
	Enfileira(item, &FILA);

	fprintf(output, "dump\n");
	while(!Vazia(FILA)) {
		n = FILA.Frente->Prox->Item;
		// printf("\nn\n");
		// print_page(n.Chave);
		// printf("\nn\n");

		if(!n.Chave->isLeaf) {
			for(i=0; i<n.Chave->count+1; i++) {
				load_child(n.Chave, i, order); // load child already queue
			}
		}

		dump_page(n.Chave, output);
		Desenfileira(&FILA, &n);
	}
	fprintf(output, "dump\n");
}
void dump_page(Page *page, FILE *output) {
	int i;
	for(i=0; i<page->count; i++) {
		fprintf(output, "%d,", page->data[i].key);
	}
	fprintf(output, "\n");
}