#include <stdio.h>
#define MAX 1000

typedef struct {
	int a, b, c, d;
} Line;

Line lines[MAX];

int inverse(int p, int a) {
	int c = 0; //contador de linhas
	int _p = p, _a = a; //auxiliares
	int r; //resto da divisao
	int d; //resultado da divisão
	do {
		r = _p%_a;
		d = _p/_a;

		lines[c].a = _p;
		lines[c].b = _a;
		lines[c].c = d;
		lines[c].d = r;


		_p = _a;
		_a = r;

		printf("\n%d = %d*%d + %d", lines[c].a, lines[c].b, lines[c].c, lines[c].d);

		c++;
	} while(r != 1 && r != 0);

	if(r == 0)
        return -1; //não é inversível

    int i, A, B, C, D, auxB;
    int minus = -1;

    A = lines[c-1].a;
    B = 1;
    C = -lines[c-1].b;
    D = lines[c-1].c;
    printf("\n\n\n1 = %d*%d + %d*%d", A, B, C, D);

    for(i=c-2; i>=0; i--) {
        A = lines[i].a;
        auxB = B;
        B = D;
        C = lines[i].b;
        D = D * lines[i].c + auxB;

        A *= pow(minus, c-i-1);
        C *= pow(minus, c-i);

        printf("\n1 = %d*%d + %d*%d", A, B, C, D);
	}

    if(C < 0)
        D = -D;

	printf("\n\n\tO inverso de %d em %d eh: %d\n\n", a, p, D);
}

int main() {
    inverse(1234, 55);
}
