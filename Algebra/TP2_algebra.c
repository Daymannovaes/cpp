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

    int one = lines[c-1].d;
    for(i=c-1; i>=0; i++) {
		one = lines[c].a - lines[c].b * lines[c].c;

	}
}

int main() {
    inverse(48, 34);
}
