#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"

FILE *defineFile();
FILE *openFile(char *fileName);
void printMatrix(Matrix*);
void squareMatrix(Matrix*);
void multiplyMatrix(Matrix*, Matrix*, Matrix*);
void subtractMatrix(Matrix*, Matrix*, Matrix*);
Matrix *copyMatrix(Matrix*);
Matrix *copyMatrixConfig(Matrix*);
void convergeMatrix(Matrix*);
int keepConverging(int, Matrix*, Matrix*);
double norm(Matrix*);
double *sort(double*, int);
void printRank(Matrix*, int);


int main() {
    FILE *file;
    Matrix *matrix;

    matrix = initMatrix();

    fileToMatrix(file, matrix);

    stocatic(matrix);
    fromStocatic(matrix);

    convergeMatrix(matrix);

    printRank(matrix, matrix->pages);
    return 0;
}

FILE *defineFile() {
	char *fileName;
	FILE *file = NULL;

	do {
		printf("Digite o nome do arquivo: ");
		scanf("%s", fileName);

		file = openFile(fileName);
	} while(file == NULL);

	return file;
}

FILE *openFile(char *fileName) {
    FILE *file;
    file = fopen(fileName, "r");

    if(file == NULL)
        printf("Erro ao abrir arquivo \"%s\".\n\n", fileName);

    return file;
}

void printMatrix(Matrix *matrix) {
    int i, j;
    int pages = matrix->pages;

    for(i=0; i<pages; i++) {
        for(j=0; j<pages; j++) {
            printf("%.12lf ", matrix->elements[i][j]);
        }
        printf("\n");
    }
}

void printRank(Matrix *rank, int pages) {
    int i;

    for(i=0; i<pages; i++) {
        printf("%d %.4lf\n", i, rank->elements[0][i]);
    }
}

void multiplyMatrix(Matrix *to, Matrix *m1, Matrix *m2) {
	int pages = to->pages;

	int i, j, k;
	double sum = 0;

	// traverse m1 rows
	for(i=0; i<pages; i++) {
		// traverse m2 columns
		for(j=0; j<pages; j++) {
			// traverse elements
			for(k=0; k<pages; k++) {
				sum += m1->elements[i][k] * m2->elements[k][j];
			}
            to->elements[i][j] = sum;
            sum = 0;
		}
        sum = 0;
	}
}
void subtractMatrix(Matrix *to, Matrix *m1, Matrix *m2) {
	int pages = to->pages;

	int i, j;

	for(i=0; i<pages; i++) {
		for(j=0; j<pages; j++) {
            to->elements[i][j] = m1->elements[i][j] - m2->elements[i][j];
		}
	}
}

Matrix *copyMatrix(Matrix *from) {
    int i, j;

    int pages = from->pages;

    Matrix *to;
    to = initMatrix();
    to->pages = pages;
    allocMatrixByConfig(to);

    for(i=0; i<pages; i++) {
        for(j=0; j<pages; j++) {
            to->elements[i][j] = from->elements[i][j];
        }
    }

    return to;
}

Matrix *copyMatrixConfig(Matrix *from) {
    Matrix *to = initMatrix();
    to->pages = from->pages;
    allocMatrixByConfig(to);

    return to;
}

void convergeMatrix(Matrix *matrix) {
    Matrix *originalCopy = copyMatrix(matrix);
    Matrix *copy;
    int n = 1;

    do {
        copy = copyMatrix(matrix);
        multiplyMatrix(matrix, copy, originalCopy);
        n++;

    } while(keepConverging(n, matrix, copy));
}

int keepConverging(int n, Matrix *actual, Matrix *previous) {
    if(n >= 2000)
        return 0;

    Matrix *diff = copyMatrixConfig(actual);
    subtractMatrix(diff, actual, previous);

    return norm(diff) > 10e-12;
}

double norm(Matrix *matrix) {
    int i, j;
    int pages = matrix->pages;

    double sum = 0;

    for(i=0; i<pages; i++) {
        for(j=0; j<pages; j++) {
            sum += matrix->elements[i][j] * matrix->elements[i][j];
        }
    }

    return sum;
}

double *sort(double *value, int pages) {
    int i, j;

    double aux;
    int maxi = 0;
    for(i=0; i<pages; i++) {
        for(j=i+1; j<pages; j++) {
            if(value[j] > value[maxi]) {
                maxi = j;
            }
        }

        aux = value[i];
        value[i] = value[maxi];
        value[maxi] = aux;
    }

    return value;
}
