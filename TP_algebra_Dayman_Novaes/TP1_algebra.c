#include <stdio.h>
#include <stdlib.h>
#include <math.h>


// ----- VAR DECLARATIONS
int A, P, E;
int a, n, e;


// ----- FUNCTIONS DECLARATIONS
int stage1(int, int, int);
int stage2();
int stage3();
int stage4();
int stage5();


// ----- FUNCTION IMPLEMENTATION

//alias
int exponentiation(int a, int e, int _n) {
    return stage1(a, e, _n);
}

int stage1(int a, int e, int _n) {
	A = a;
	P = 1;
	E = e;
    n = _n;

	return stage2();
}

int stage2() {
	if(E == 0) {
		return P;
	}

	return stage3();
}

int stage3() {
	if(E%2 == 1) {
		P = (A*P)%n;
		E = (E-1)/2;

		return stage5();
	}
	else {
		return stage4();
	}
}

int stage4() {
    E = E/2;
    return stage5();
}

int stage5() {
	A = (A*A)%n;
    return stage2();
}

int rmax(int r, int p) {
    return r >= (pow(2, p/2) - 1)/(2*p);
}

int main() {
    int p, q, r;
    int exponentiationResult;

    printf("Digite p: ");
    scanf("%d", &p);

    r = 0;
    while(!rmax(r, p)) {
        q = (r*2*p) + 1;
        exponentiationResult = exponentiation(2, p, q);

        printf("\n2^%d mod %d = %d", p, q, exponentiationResult);

        if(exponentiationResult == 1) {
            printf("\n\n\t%d e' um fator de M(%d) = 2^%d - 1\n\n", q, p, p);
            return 0;
        }
        r++;
    }

    printf("\n\n\tM(%d) = 2^%d - 1 eh um numero primo.\n\n", p, p);
    return 0;
}
