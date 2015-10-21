#include <stdio.h>
#include <string.h>
#define MAX 5
struct produto {
    char descricao[40];
    float valor;
};
int main() {
    struct produto prods[MAX]; /* definindo um vetor de 5
    posicoes para o struc produto */
    int i;

    for (i=0; i<MAX; i++) {
        puts("Nome do Produto?");
        gets(prods[i].descricao);
        puts("Valor do Produto?");
        scanf("%f", &prods[i].valor);
        getchar(); // Limpa o buffer de teclado
    }

    printf("\n\n");

    for (i=0; i<MAX; i++) {
        if(prods[i].valor > 120) {
            printf("Descricao: %s - Valor: R$ %.2f\n",
            prods[i].descricao, prods[i].valor);
        }
    }
    return 0;
}
