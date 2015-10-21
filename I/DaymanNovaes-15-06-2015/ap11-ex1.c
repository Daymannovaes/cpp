#include <stdio.h>

int main() {
    int a1, r, n;

    printf("Digite o termo inicial: ");
    scanf("%d", &a1);
    printf("Digite a razao: ");
    scanf("%d", &r);
    printf("Digite quantos termos deseja gerar: ");
    scanf("%d", &n);

    pg(a1, r, n);
    printf("\n");
}

void pg(int a1, int r, int n) {
    _pg(a1, r, n, 1);
}

void _pg(int a, int r, int n, int cont) {
    printf("\nTermo %d: %d", cont, a);
    if(cont < n)
        _pg(a*r, r, n, cont+1);
}


