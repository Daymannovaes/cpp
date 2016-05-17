#ifndef STRUCTS
#define STRUCTS

typedef struct Point {
	int x, y;
} Point;

typedef struct Map {
	int columns, rows;
	int **points;
} Map;

#endif
