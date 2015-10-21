#include <stdio.h>

int main() {
    int n;

    printf("Digite o valor a ser convertido para binario: ");
    scanf("%d", &n);

    printf("\n\t%d em binario: ", n);
    calculaBinario(n);
    printf("\n");
}

void calculaBinario(int n) {
    if(n > 1)
        calculaBinario(n/2);

    printf("%d", n%2);
}


