#include <stdio.h>
#include <string.h>
struct tipo_endereco {
    char rua [50];
    int numero;
    char bairro [20];
    char cidade [30];
    char sigla_estado [3];
    long int CEP;
};

struct ficha_pessoal {
    char nome [50];
    long int telefone;
    struct tipo_endereco endereco;
};

main (void) {
    struct ficha_pessoal ficha;
    strcpy (ficha.nome,"Luiz Osvaldo Silva");
    ficha.telefone=4921234;
    strcpy (ficha.endereco.rua,"Rua das Flores");
    ficha.endereco.numero=10;
    strcpy (ficha.endereco.bairro,"Cidade Velha");
    strcpy (ficha.endereco.cidade,"Belo Horizonte");
    strcpy (ficha.endereco.sigla_estado,"MG");
    ficha.endereco.CEP=31340230;


    printf("\t\tFicha Pessoal: \n");
    printf("\t\t--- Nome: %s\n", ficha.nome);
    printf("\t\t--- telefone: %d\n", ficha.telefone);
    printf("\t\t\t--- Endereco:\n");
    printf("\t\t\t    --- Rua: %s\n", ficha.endereco.rua);
    printf("\t\t\t    --- Numero: %d\n", ficha.endereco.numero);
    printf("\t\t\t    --- Bairro: %s\n", ficha.endereco.bairro);
    printf("\t\t\t    --- Cidade: %s\n", ficha.endereco.cidade);
    printf("\t\t\t    --- Estado: %s\n", ficha.endereco.sigla_estado);
    printf("\t\t\t    --- CEP: %d\n", ficha.endereco.CEP);
    return 0;
}
