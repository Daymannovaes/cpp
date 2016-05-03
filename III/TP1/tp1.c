#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "structs.h"
#include "constructors.h"

#define MAX_BUFF 64
#define READ_STR "%63s"

void read_line_from(FILE *file, char *str);
void remove_new_line(char *str);
void insert_field_in_record(Record *record, Field field);
void insert(Page *root, Record *record);
Tree *command_add(FILE *output, FILE *input, int order, int fieldCount, int keyNumber, Tree *tree, int recordCount);
void print_record(Record *record);
void print_page(Page *page);
void print_tree(Tree *tree, int printSelf);

void insert_record_in_file(Record *record, FILE *file);
Tree *insert_record_in_tree(Tree *tree, int key, int value, int order);
void insert_record_in_leaf(Tree *tree, Page *page, Pair *data, int order);
Tree *split_and_insert_in_leaf(Tree *tree, Page *page, Pair *data, int order);
Tree *insert_record_in_parent(Tree *tree, Page *left, Page *right, Pair *data, int order);
void insert_record_in_internal(Page *page, Page *left, Page *right, Pair *data);
Tree *split_and_insert_in_internal(Tree *tree, Page *page, Page *left, Page *right, Pair *data, int order);

int main(int argc, char const *argv[]) {
    setbuf(stdout, NULL);
	Tree *tree;

	FILE *output, *input;
	int order;
	int fieldCount, keyNumber;

	output 		= fopen(argv[1], "wb");
	input  		= fopen(argv[2], "r");
	order  		= atoi(argv[3]);
	fieldCount 	= atoi(argv[4]);
	keyNumber 	= atoi(argv[5]);

	tree = create_leaf(order);

	char str[MAX_BUFF];
	int recordCount = 0;

	while(!feof(input)) {
		read_line_from(input, str);

		if(strcmp(str, "add") == 0) {
			tree = command_add(output, input, order, fieldCount, keyNumber, tree, recordCount);
			recordCount++;
		}
		if(strcmp(str, "search") == 0) {
		}
		if(strcmp(str, "dump") == 0) {
		}
	}

	print_tree(tree, true);
	return 0;
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

Tree *command_add(FILE *output, FILE *input, int order, int fieldCount, int keyNumber, Tree *tree, int recordCount) {
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
	free_record(record);
	return insert_record_in_tree(tree, record->key, recordCount, order);
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
void print_tree(Tree *tree, int printSelf) {
	if(printSelf){
		printf("\nlevel c(%d)", tree->count);
		print_page(tree);
		printf("\n");
	}

	int i;
	if(tree->pointers != NULL) {
		for(i=0; i<tree->count+1; i++) {
				print_page(tree->pointers[i]);
			printf(" | ");
		}
		for(i=0; i<tree->count+1; i++) {
			printf("\nsons of (%d|%d) \n", tree->pointers[i]->data[0].key, tree->pointers[i]->data[0].value);
				print_tree(tree->pointers[i], false);
			printf(" | ");
		}
	}
}
void insert_record_in_file(Record *record, FILE *file) {
	fprintf(file, "%d", record->key);

	int i;
	for(i=0; i<record->count; i++) {
		fprintf(file, " %s", record->fields[i]);
	}

	fprintf(file, "\n");
}
Tree *insert_record_in_tree(Tree *tree, int key, int value, int order) {
	Pair *data = create_pair(key, value);

	if(tree->isLeaf) {
		if(tree->count < order)
			insert_record_in_leaf(tree, tree, data, order);
		else
			return split_and_insert_in_leaf(tree, tree, data, order);
	}
	else {
		Page *page = tree;
		int index;
		while(!page->isLeaf) {
			index = 0;
			while (index < page->count && page->data[index].key <= data->key)
				index++;

			page = page->pointers[index];
		}

		// printf("\n leaf to insert (%d) begin with: (%d|%d)", key, page->data[0].key, page->data[0].value);

		if(page->count < order)
			insert_record_in_leaf(tree, page, data, order);
		else
			return split_and_insert_in_leaf(tree, page, data, order);
	}

	free(data);
	return tree;
}

void insert_record_in_leaf(Tree *tree, Page *page, Pair *data, int order) {
	int i, index;

	index = 0;
	while (index < page->count && page->data[index].key < data->key)
		index++;

	for (i = page->count; i > index; i--) {
		page->data[i] = page->data[i - 1];
	}

	// printf("\ninserting (%d|%d) in %d", key, value, index);
	page->data[index].key = data->key;
	page->data[index].value = data->value;
	page->count++;
}

void insert_record_in_internal(Page *page, Page *left, Page *right, Pair *data) {
	int i, index;

	index = 0;
	while (index < page->count && page->data[index].key < data->key)
		index++;

	for (i = page->count+1; i > index; i--) {
		page->data[i] = page->data[i - 1];
		page->pointers[i] = page->pointers[i - 1];
	}

	page->pointers[index] = left;
	page->pointers[index+1] = right;

	page->data[index].key = data->key;
	page->data[index].value = data->value;
	page->count++;
}

/** 
 * create two new pages from the *page, point this page
 * as parent 
 */
Tree *split_and_insert_in_leaf(Tree *tree, Page *left, Pair *data, int order) {
	Page *right;
	Pair *auxPairs;
	int index, splitIndex, i, j;

	auxPairs = malloc((order+1) * sizeof(Pair));

	index = 0;
	while (index < order && left->data[index].key < data->key)
		index++;

	for (i = 0, j = 0; i < left->count; i++, j++) {
		if (j == index) j++;
		auxPairs[j].key = left->data[i].key;
		auxPairs[j].value = left->data[i].value;
	}
	auxPairs[index].key = data->key;
	auxPairs[index].value = data->value;

	splitIndex = order%2 == 0 ? order/2 : order/2 + 1;

	left->count = 0;
	right = create_leaf(order);

	for (i = 0; i < splitIndex; i++) {
		left->data[i].key = auxPairs[i].key;
		left->data[i].value = auxPairs[i].value;
		left->count++;
	}

	for (i = splitIndex, j = 0; i < order+1; i++, j++) {
		right->data[j].key = auxPairs[i].key;
		right->data[j].value = auxPairs[i].value;
		right->count++;
	}

	free(auxPairs);
	right->parent = left->parent;

	data->key = right->data[0].key;
	data->value = right->data[0].value;

	return insert_record_in_parent(tree, left, right, data, order);
}
Tree *split_and_insert_in_internal(Tree *tree, Page *leftParent, Page *left, Page *right, Pair *data, int order) {
	Page *rightParent;
	Pair *auxPairs;
	PagePointer *auxPointers;
	int index, splitIndex, i, j;

	auxPairs = malloc((order+1) * sizeof(Pair));
	auxPointers = malloc((order+2) * sizeof(PagePointer));

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
		leftParent->count++;
	}
	leftParent->pointers[splitIndex] = auxPointers[splitIndex];

	for (i = splitIndex, j = 0; i < order+1; i++, j++) {
		rightParent->data[j].key = auxPairs[i].key;
		rightParent->data[j].value = auxPairs[i].value;
		rightParent->pointers[j] = auxPointers[i];
		rightParent->count++;
	}
	rightParent->pointers[j] = auxPointers[order+1];

	free(auxPairs);
	free(auxPointers);
	rightParent->parent = leftParent->parent;

	data->key = rightParent->data[0].key;
	data->value = rightParent->data[0].value;

	return insert_record_in_parent(tree, leftParent, rightParent, data, order);
}

Tree *insert_record_in_parent(Tree *tree, Page *left, Page *right, Pair *data, int order) {
	Page *parent = left->parent;
	int index;

	// left equals root (tree)
	if(parent == NULL) {
		parent = create_internal(order);
		tree = parent;

		left->parent = tree;
		right->parent = tree;
	}

	if(parent->count < order)
		insert_record_in_internal(parent, left, right, data);
	else {
		return split_and_insert_in_internal(tree, parent, left, right, data, order);
	}

	return tree;
}