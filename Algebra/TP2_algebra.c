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

	if(r == 0) {
        printf("\n\n\tO numero nao eh inversivel.\n");
        return -1; //não é inversível
	}

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

	printf("\n\n\tO inverso de %d em %d eh: %d.\n\n", a, p, D);
}

void phi(int k) {
    int x;
    float y;

    x = ceil(sqrt(k));
    y = sqrt(x*x - k);
    printf("\n  x  |  y \n", k);
    printf("  %d  |  %f  \n", x, y);
    while((int)y != y) {
        x++;
        y = sqrt(x*x - k);

        printf("  %d  |  %f  \n", x, y);

        //getch();
    }

    //se for primo
    if(x+y == k) {
        printf("\n\t%d primo", k);
        printf("\n\tphi(%d) = %d - 1 = %d\n ", k, k, k-1);
    }
    else {
        printf("\n\t%d = (x + y)(x - y) = (%d + %.0f)(%d - %0.f) = %.0f*%.0f", k, x, y, x, y, (x+y), (x-y));
        printf("\n\tphi(%d) = (%0.f - 1)(%0.f - 1) = %0.f*%0.f = %0.f\n", k, x+y, x-y, x+y-1, x-y-1, (x+y-1)*(x-y-1));
    }
}

void menu() {
    int op;
    printf("\n");

      printf("\n\t___________________________");
    printf("\n\n\tQual opcao deseja escolher?");
      printf("\n\t___________________________");
    printf("\n\n\t 1. %s", "Calcular o inverso de um numero");
    printf("\n\n\t 2. %s", "Calcular phi de um numero");
    printf("\n\n\t 3. %s", "Gerar numeros e testar divisibilidade por primos menores que 5000");
    printf("\n\n\t 4. %s", "Sair");

    printf("\n\n\t\t > .\b");
    scanf("%d", &op);

    switch(op) {
    case 1:
        menuInverse();
        break;
    case 2:
        menuPhi();
        break;
    case 3:
        break;
    case 4:
        exit(0);
    }

    menu();
}


void menuInverse() {
    printf("\n");

    int n1, n2;
    printf("\tDigite o modulo: ");
    scanf("%d", &n1);

    printf("\n\tDigite o numero a ser calculado o inverso: ");
    scanf("%d", &n2);

    inverse(n1, n2);

    printf("\n\tAperte qualquer tecla para retornar.");
    getch();
}
void menuPhi() {
    printf("\n");

    int k;
    printf("\tDigite k: ");
    scanf("%d", &k);

    phi(k);

    printf("\n\tAperte qualquer tecla para retornar.");
    getch();
}

int main() {
    menu();
}
