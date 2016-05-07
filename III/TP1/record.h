#include <stdio.h>

#ifndef RECORD
#define RECORD

#define MAX_BUFF 1024
typedef char Field[MAX_BUFF];	// field is a string
typedef struct Record {
	int key;
	int count;					// number of fields in this record
	Field *fields;				// each record has many fields
} Record;

Record *create_record(int order);
void free_record(Record *record);
void insert_field_in_record(Record *record, Field field);
void insert_record_in_file(Record *record, FILE *file);

#endif