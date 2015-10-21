#include <stdlib.h>
#include "matrix.h"

Matrix *initMatrix() {
    return (Matrix *)malloc(sizeof(Matrix));
}

void fileToMatrix(FILE *file, Matrix *matrix) {
    defineConfig(file, matrix);

    allocMatrixByConfig(matrix);

    defineElements(file, matrix);
}

void defineConfig(FILE *file, Matrix *matrix) {
	definePages(file, matrix);
	defineDamping(file, matrix);
}
void allocMatrixByConfig(Matrix *matrix) {
    int pages = matrix->pages;
    int i;

    matrix->elements = (double **)malloc(pages * sizeof(double*));
    for(i=0; i < pages; i++) {
        matrix->elements[i] = (double *)calloc(pages, sizeof(double));
    }
}

void definePages(FILE *file, Matrix *matrix) {
    int pages = 0;
    fscanf(stdin, "%d", &pages);

    //if(pages <= 1 || pages > 1000)
    //    printf("Numero de paginas deve estar entre 2 e 1000");

    matrix->pages = pages;
}
void defineDamping(FILE *file, Matrix *matrix) {
    double damping = 0;
    fscanf(stdin, "%lf", &damping);

    //if(damping < 0 || damping > 1)
    //    printf("Damping deve estar entre 0 e 1");

    matrix->damping = damping;
}

void defineElements(FILE *file, Matrix *matrix) {
    fileToElements(file, matrix);
    normalize(matrix);
}

void fileToElements(FILE *file, Matrix *matrix) {
    int i, j;
    while(!feof(stdin)) {
        fscanf(stdin, "%d", &i);
        fscanf(stdin, "%d", &j);

        matrix->elements[i][j] = 1;
    }
}
void normalize(Matrix *matrix) {
    int j, i, pages;
    pages = matrix->pages;
    i = nullLineIndex(matrix, 0);

    while(i != -1) {
        for(j=0; j<pages; j++) {
            matrix->elements[i][j] = 1;
        }

        i = nullLineIndex(matrix, i+1);
    }
}
int nullLineIndex(Matrix *matrix, int init) {
    int i, j;
    int pages = matrix->pages;

	for(i=init; i<pages; i++) {
        for(j=0; j<pages; j++) {
            if((int)matrix->elements[i][j] == 1) {
                if(i+1 == matrix->pages)
                    return -1;
                i++;
                j=0;
            }
        }
        return i;
	}

	return -1;
}

void stocatic(Matrix *matrix) {
	int i, pages;
	double *row, total;
	pages = matrix->pages;

	for(i=0; i<pages; i++) {
		row = matrix->elements[i];

		total = totalInRow(row, pages);
		changeOneTo(row, 1/total, pages);
	}
}

void fromStocatic(Matrix *matrix) {
	int i, j, pages;
	double damping;
	pages = matrix->pages;
	damping = matrix->damping;

	for(i=0; i<pages; i++) {
        for(j=0; j<pages; j++) {
            matrix->elements[i][j] = (1 - damping) * matrix->elements[i][j] + damping/pages;
        }
	}
}

double totalInRow(double *row, int pages) {
	int i;
	double total = 0;

	for(i=0; i<pages; i++)
		total += row[i];

	return total;
}

void changeOneTo(double *row, double to, int pages) {
	int i;
	for(i=0; i<pages; i++) {
		row[i] = (int)row[i] == 1 ? to : 0;
	}
}

