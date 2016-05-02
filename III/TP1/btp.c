#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_BUFF 64
#define READ_STR %63s

typedef char field[MAX_BUFF];		// field is a string
typedef struct Record {
	int key;
	int count;				// number of fields in this record
	field *fields;			// each record has many fields
} Record;

typedef struct Page *PagePointer;

typedef struct Page {
	int isLeaf;

	int count;				// number of records in this page
	Record *records;		// array of records
	PagePointer *pointers;	// array of pages

	PagePointer parent;		// parent page
} Page;

void insert(Page *root, Record *record);

void removeNewLine(char *str) {
    if (str != NULL && str[strlen(str) - 1] == '\n')
        str[strlen(str) - 1] = '\0';
}
void readLineFrom(FILE *file, char *str) {
    fscanf(file, READ_STR, str);
    removeNewLine(str);
}

void command_add(FILE *output, FILE *input, int order, int fieldCount, int keyNumber) {
	int i;

	Field field;

	for(i=0; i<fieldCount; i++) {
		readLineFrom(input, field);

		if(i == keyNumber)
			record->key = atoi(field);
		else
			insert_field_in_record(record, field);
	}
}

int main(int argc, char const *argv[]) {
	Page *root;

	FILE *output, *input;
	int order;
	int fieldCount, keyNumber;

	output 		= fopen(argv[1], "wb");
	input  		= fopen(argv[2], "r");
	order  		= atoi(argv[3]);
	fieldCount 	= atoi(argv[4]);
	keyNumber 	= atoi(argv[5]);

	char str[MAX_BUFF];

	while(!feof(input)) {
		readLineFrom(input, str);

		// command
		switch(str) {
			case "add":
				command_add(output, input, order, fieldCount, keyNumber);
				break;
			case "search":
				break;
			case "dump"::
				break;
		}
	}

	return 0;
}