#include <stdio.h>
#include <stdlib.h>
#define N 100
#include "TADArvoreAVL.h"

FILE *arquivo(){ //Abre um arquivo do qual serao lidos os valores a ser inseridos na arvore
    FILE *fp;
    fp=fopen("Numeros.txt", "r");
    if(fp==NULL) {
        printf("Erro ao abrir arquivo.\n");
        return;
    }
    return fp;
}

int main(){
    ArvoreAVL* arvAVL; //inicializacao de variaveis
    FILE *fp;
    int insere,i, dados[N];

    fp=arquivo();
    arvAVL = cria_ArvoreAVL();// chama a funcao que cria a arvore

    for(i=0; i<N; i++){ //le do arquivo os numeros a serem inseridos na arvore
        fscanf(fp, "%d", &dados[i]);
    }
    for(i=0;i<N;i++){ //os valores sao entao inseridos na arvore
        insere = insere_ArvoreAVL(arvAVL,dados[i]);
    }

    printf("\n\tExemplo de Arvore AVL:\n (Valores repetidos sao impressos uma unica vez)\n"); //impressao da arvore, altura do no e fator de balanceamento
    imprime_ArvoreAVL(arvAVL);
    printf("\n\n");

    return 0;
}
