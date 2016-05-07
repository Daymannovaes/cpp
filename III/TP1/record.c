#include <stdlib.h>
#include <string.h>
#include "record.h"

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

void insert_field_in_record(Record *record, Field field) {
	strcpy(record->fields[record->count], field);
	record->count++;
}
void insert_record_in_file(Record *record, FILE *file) {
	fprintf(file, "%d", record->key);

	int i;
	for(i=0; i<record->count; i++) {
		fprintf(file, "\t%s", record->fields[i]);
	}

	fprintf(file, "\n");
}