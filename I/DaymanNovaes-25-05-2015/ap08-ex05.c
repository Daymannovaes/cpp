#include <stdio.h>
#include <string.h>
#define MAX 10
struct Pessoa {
    char nome[40];
    float peso, altura;
    int idade;
};
int main() {
    struct Pessoa vetorCadastro[MAX];
    int i, n;

    printf("Quantas pessoas quer cadastrar: ");
    scanf("%d", &n);

    for (i=0; i<n; i++) {
        puts("Nome?");
        fflush(stdin);
        fgets(vetorCadastro[i].nome, 40, stdin);
        fflush(stdin);
        puts("Peso");
        scanf("%f", &vetorCadastro[i].peso);
        puts("Altura");
        scanf("%f", &vetorCadastro[i].altura);
        puts("Idade");
        scanf("%d", &vetorCadastro[i].idade);
    }

    printf("\n\n");

    for (i=0; i<n; i++) {
        printf("\nPessoa %d\n", i+1);
        printf("\n\tNome: %s", vetorCadastro[i].nome);
        printf("\n\tPeso: %f", vetorCadastro[i].peso);
        printf("\n\tAltura: %f", vetorCadastro[i].altura);
        printf("\n\tIdade: %d", vetorCadastro[i].idade);
    }

    return 0;
}
