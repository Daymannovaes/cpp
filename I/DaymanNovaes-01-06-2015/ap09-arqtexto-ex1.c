#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <ctype.h>

#define MAX 80

char opcao_menu() {
    system("cls");
    printf("(L)istar notas\n");
    printf("(F)im\n");
    printf("> ");
    return (toupper(getche()));
}

void listar_notas() {
    int num, notas;
    float n1, n2, media;

    char *nome;
    char buf[MAX];
    FILE *arq;

    arq = fopen("dados.txt", "r");
    if(arq == NULL) {
        printf("Erro ao abrir arquivo\n");
        return;
    }
    printf("\n");
    printf("NUM |           NOME           |  N1  |  N2  \n");
    printf("----+--------------------------+------+------\n");

    notas = 0;
    media = 0;
    fgets(buf, MAX, arq);
    while(!feof(arq)) {
        num = atoi(strtok(buf, ","));
        nome = strtok(NULL, ",");
        n1 = atof(strtok(NULL, ","));
        n2 = atof(strtok(NULL, ","));

        printf("%03d | %-24s | %4.1f | %4.1f\n", num, nome, n1, n2);
        notas = notas + 2;
        media = media + n1 + n2;
        fgets(buf, MAX, arq);
    }
    printf("----+--------------------------+------+------\n");
    media = media/notas;
    printf("Media das notas = %4.1f\n", media);

    fclose(arq);
}

int main() {
    char op;
    do {
        op = opcao_menu();
        if(op == 'L')
            listar_notas();
        printf("\n");
        system("pause > null");
    } while(op != 'F');

    return 0;
}








