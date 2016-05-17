#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_BUFF 16
#define READ_STR "%15s"

// ----- HELPER FUNCTIONS (used in development)
// ---------------------------------------- //


// ----- HIGH LEVEL COMMAND FUNCTIONS
// ---------------------------------------- //


// ----- FILE HANDLER FUNCTIONS
// ---------------------------------------- //


// ----- CREATORS FUNCTIONS
Point *create_point(int x, int y);
// ---------------------------------------- //

typedef struct Point {
	int x, y;
} Point;


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

	char str[MAX_BUFF];
	int width, height;

	fscanf(input, READ_STR, str);
	height = atoi(str);
	fscanf(input, READ_STR, str);
	width = atoi(str);

	printf("height %d and width %d", height, width);

	return 0;
}

Point *create_point(int x, int y) {
	Point *point;
	point = malloc(sizeof(Point));

	point->x = x;
	point->y = y;

	return point;
}