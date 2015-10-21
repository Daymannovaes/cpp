#include <stdio.h>

typedef struct {
    int pages; //número de páginas
    double damping;
    double **elements;
} Matrix;

Matrix *initMatrix();
void fileToMatrix(FILE*, Matrix*);
    void defineConfig(FILE*, Matrix*);
        void definePages(FILE*, Matrix*);
        void defineDamping(FILE*, Matrix*);
    void allocMatrixByConfig(Matrix*);
    void defineElements(FILE*, Matrix*);
        void fileToElements(FILE*, Matrix*);
        void normalize(Matrix*);
            int nullLineIndex(Matrix*, int);

void stocatic(Matrix*);
void fromStocatic(Matrix*);
double totalInRow(double*, int);
void changeOneTo(double*, double, int);

