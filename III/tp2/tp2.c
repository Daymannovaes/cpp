#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "structs.h"
#include "printer.h"

#define MAX_BUFF 16
#define READ_STR "%15s"

// ----- CREATORS FUNCTIONS
Point *create_point(int x, int y);
Map *create_map(int rows, int columns, FILE *input);
// ---------------------------------------- //

// docs
// https://docs.google.com/document/d/1buH0mK6U_ZebSpookLaqd_0erx5hQUuMcuUff1sGtCo/edit#heading=h.rz194zb44u8t

int main(int argc, char const *argv[]) {
	FILE *input;
	int x, y;
	Point *origin, *destiny, *step;

	input 	= fopen(argv[1], "r");
	
	x		= atoi(argv[2]);
	y		= atoi(argv[3]);
	origin 	= create_point(x, y);

	x		= atoi(argv[4]);
	y		= atoi(argv[5]);
	destiny = create_point(x, y);

	x		= atoi(argv[6]);
	y		= atoi(argv[7]);
	step    = create_point(x, y);

	int columns, rows;
	char str[MAX_BUFF];

	fscanf(input, READ_STR, str);
	columns = atoi(str);
	fscanf(input, READ_STR, str);
	rows = atoi(str);

	Map *map;
	map = create_map(rows, columns, input);
	print_map(map);

	fclose(input);
	return 0;
}

Point *create_point(int x, int y) {
	Point *point;
	point = malloc(sizeof(Point));

	point->x = x;
	point->y = y;

	return point;
}

Map *create_map(int rows, int columns, FILE *input) {
	Map *map;
	int i, j;
	char str[MAX_BUFF];

	map = malloc(sizeof(Map));
	map->rows = rows;
	map->columns = columns;

	map->points = malloc(rows * sizeof(int*));
	for(i=0; i<rows; i++) {
		map->points[i] = malloc(columns * sizeof(int));

		for(j=0; j<columns; j++) {
			fscanf(input, READ_STR, str);
			map->points[i][j] = atoi(str);
		}
	}

	return map;
}
