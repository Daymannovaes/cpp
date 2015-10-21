#include <stdio.h>
#include <string.h>
#define MAX 10
struct Pessoa {
    char nome[40];
    float peso, altura;
    int idade;
};

struct Pessoa nova_pessoa() {
    struct Pessoa pessoa;

    fflush(stdin);
    fgets(pessoa.nome, 40, stdin);
    fflush(stdin);
    puts("Peso");
    scanf("%f", &pessoa.peso);
    puts("Altura");
    scanf("%f", &pessoa.altura);
    puts("Idade");
    scanf("%d", &pessoa.idade);

    return pessoa;
};

int main() {
    struct Pessoa vetorCadastro[MAX];
    int i, n;

    printf("Quantas pessoas quer cadastrar: ");
    scanf("%d", &n);

    for (i=0; i<n; i++) {
        puts("Nome?");
        vetorCadastro[i] = nova_pessoa();
    }

    printf("\n\n");

    for (i=0; i<n; i++) {
        printf("\n\nPessoa %d", i+1);
        printf("\n\tNome: %s", vetorCadastro[i].nome);
        printf("\n\tPeso: %f", vetorCadastro[i].peso);
        printf("\n\tAltura: %f", vetorCadastro[i].altura);
        printf("\n\tIdade: %d", vetorCadastro[i].idade);
    }

    return 0;
}
