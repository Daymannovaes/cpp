#include <stdio.h>
#include "printer.h"

void print_map(Map *map) {
	int i, j;

	printf("\n\n%d %d\n", map->columns, map->rows);
	for(i=0; i<map->rows; i++) {
		for(j=0; j<map->columns; j++) {
			printf("%d ", map->points[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

void print_point(Point *point) {
	printf(" (%d, %d) ", point->x, point->y);
}
void print_point_with(Point *point, char *str) {
	printf("%s\n(%d, %d) ", str, point->x, point->y);
}
void print_point_with2(Point *point, char *str1, char *str2) {
	printf("%s\n(%d, %d)\n%s", str1, point->x, point->y, str2);
}