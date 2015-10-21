#include <stdio.h>

int main() {
    int n;

    printf("Digite o valor inicial: ");
    scanf("%d", &n);

    ackerman(n);
    printf("\n");
}

void ackerman(int n) {
    _ackerman(n, 1);
}

void _ackerman(int n, int cont) {
    printf("\nTermo %d: %d", cont, n);

    if(n != 1) {
        n = !(n%2) ? (n/2) : ((3*n) + 1);
        _ackerman(n, cont+1);
    }
}


