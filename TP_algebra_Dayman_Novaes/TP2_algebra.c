#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#define MAX 1000

typedef struct {
	int a, b, c, d;
} Line;

Line lines[MAX];


void menuInverse();
void menuPhi();
void menuGen();
int inverse(int p, int a);
int isPrime(int k);
void phi(int k);
void gen();
void menu();

int inverse(int p, int a) {
	int c = 0; //contador de linhas
	int _p = p, _a = a; //auxiliares
	int r; //resto da divisao
	int d; //resultado da divis�o
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
        return -1; //n�o � invers�vel
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

	printf("\n\n\tInverso de %d em %d: %d.\n\n", a, p, D);
}

int isPrime(int k) {
    int i;

    if(k == 2)
        return 1;

    for(i=2; i<k/2; i++) {
        if(k%i == 0)
            return 0;
    }

    return 1;
}

void phi(int k) {
    int i, j;
    int terms[MAX];
    int partial = k;
    int countTerms = 0;

    for(i=2; i<k || partial != 1; i++) {
        if(isPrime(i) && partial%i == 0) {
            terms[countTerms] = i;
            countTerms++;
            partial /= i;
            i--; //try again
        }
    }


    int phiResult = 1;
    int lastTerm = terms[0];
    int countRepeatedTerms = 1;
    printf("\n\t%d = ", k);
    for(i=1; i<countTerms; i++) {

        if(terms[i] == lastTerm)
            countRepeatedTerms++;
        else {
            printf("%d^%d * ", lastTerm, countRepeatedTerms);
            phiResult *= pow(lastTerm, countRepeatedTerms) - pow(lastTerm, countRepeatedTerms-1);
            countRepeatedTerms = 1;
        }

        lastTerm = terms[i];
    }
    printf("%d^%d", lastTerm, countRepeatedTerms);
    phiResult *= pow(lastTerm, countRepeatedTerms) - pow(lastTerm, countRepeatedTerms-1);

    printf("\n\tphi(%d) = %d\n\n", k, phiResult);
}

void gen() {
	srand(time(NULL));
	int i;
	int rPrime = 1, sPrime = 1;

	int bits19 = pow(2, 19);
	int bits20 = bits19 * 2;
	
	int r = rand()%(bits20 - bits19) + bits19;
	int s = rand()%(bits20 - bits19) + bits19;
	if(r%2 == 0) r++;
	if(s%2 == 0) s++;

	printf("\n\n\tR: %d \n\tS: %d\n", r, s);

	for(i=2; i<=5000; i++) {
		if(isPrime(i)) {
			if(r%i == 0) {
				printf("\n\t R e' divisivel pelo primo %d", i);
				rPrime = 0;
			}
			if(s%i == 0) {
				printf("\n\t S e' divisivel pelo primo %d", i);
				sPrime = 0;
			}
		}
	}
	if(!rPrime) {
		printf("\n\n\tR nao e' primo");
	}
	else if((int)pow(2, r-1)%r != 1 && rPrime) {
		printf("\n\t R nao e' primo pelo teste de Miller com base = %d", 2);
	}
	else if((int)pow(3, r-1)%r != 1 && rPrime) {
		printf("\n\t R nao e' primo pelo teste de Miller com base = %d", 3);
	}
	else if((int)pow(5, r-1)%r != 1 && rPrime) {
		printf("\n\t R nao e' primo pelo teste de Miller com base = %d", 5);
	}
	else if((int)pow(5, r-1)%r != 1 && rPrime) {
		printf("\n\t R nao e' primo pelo teste de Miller com base = %d", 5);
	}
	else if((int)pow(7, r-1)%r != 1 && rPrime) {
		printf("\n\t R nao e' primo pelo teste de Miller com base = %d", 7);
	}
	else if((int)pow(11, r-1)%r != 1 && rPrime) {
		printf("\n\t R nao e' primo pelo teste de Miller com base = %d", 11);
	}
	else if((int)pow(13, r-1)%r != 1 && rPrime) {
		printf("\n\t R nao e' primo pelo teste de Miller com base = %d", 13);
	}
	else if((int)pow(17, r-1)%r != 1 && rPrime) {
		printf("\n\t R nao e' primo pelo teste de Miller com base = %d", 17);
	}
	else if((int)pow(19, r-1)%r != 1 && rPrime) {
		printf("\n\t R nao e' primo pelo teste de Miller com base = %d", 19);
	}
	else if((int)pow(23, r-1)%r != 1 && rPrime) {
		printf("\n\t R nao e' primo pelo teste de Miller com base = %d", 23);
	}
	else {
		printf("\n\n\t R provavelmente e' primo");
	}

	if(!sPrime) {
		printf("\n\n\tS nao e' primo");
	}
	else if((int)pow(2, s-1)%r != 1 && sPrime) {
		printf("\n\t S nao e' primo pelo teste de Miller com base = %d", 2);
	}
	else if((int)pow(3, s-1)%r != 1 && sPrime) {
		printf("\n\t S nao e' primo pelo teste de Miller com base = %d", 3);
	}
	else if((int)pow(5, s-1)%r != 1 && sPrime) {
		printf("\n\t S nao e' primo pelo teste de Miller com base = %d", 5);
	}
	else if((int)pow(5, s-1)%r != 1 && sPrime) {
		printf("\n\t S nao e' primo pelo teste de Miller com base = %d", 5);
	}
	else if((int)pow(7, s-1)%r != 1 && sPrime) {
		printf("\n\t S nao e' primo pelo teste de Miller com base = %d", 7);
	}
	else if((int)pow(11,s-1)%r != 1 && sPrime) {
		printf("\n\t S nao e' primo pelo teste de Miller com base = %d", 11);
	}
	else if((int)pow(13, s-1)%r != 1 && sPrime) {
		printf("\n\t S nao e' primo pelo teste de Miller com base = %d", 13);
	}
	else if((int)pow(17, s-1)%r != 1 && sPrime) {
		printf("\n\t S nao e' primo pelo teste de Miller com base = %d", 17);
	}
	else if((int)pow(19, s-1)%r != 1 && sPrime) {
		printf("\n\t S nao e' primo pelo teste de Miller com base = %d", 19);
	}
	else if((int)pow(23, s-1)%r != 1 && sPrime) {
		printf("\n\t S nao e' primo pelo teste de Miller com base = %d", 23);
	}
	else {
		printf("\n\n\t S provavelmente e' primo");
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
        menuGen();
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
}
void menuPhi() {
    printf("\n");

    int k;
    printf("\tDigite k: ");
    scanf("%d", &k);

    phi(k);
}

void menuGen() {
    printf("\n");
    printf("Nothing here yet\n");


    gen();
}


int main() {
    menu();
}
