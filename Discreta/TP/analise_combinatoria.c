#include <stdio.h>

#define type_sn "O %s dado deve ser 's' ou 'n'"
#define range "O %s dado deve estar em %d e %d"
#define gt "O %s dado deve ser maior que %d"
#define type_again "\nDigite novamente: "
#define imprime_str "\n---- %s podemos contar %.0f %s. ----"

#define ordem_repete 1
#define ordem_nao_repete 2
#define nao_ordem_repete 3
#define nao_ordem_nao_repete 4
int combinacao(char o, char r) {
    if(o == 's' || o == 'S') {
        if(r == 's' || r == 'S')
            return ordem_repete;
        return ordem_nao_repete;
    }
    if(r == 's' || r == 'S')
        return nao_ordem_repete;
    return nao_ordem_nao_repete;
}

void leDados(char *o, char *re, int *n, int *r) {
    fflush(stdin);
    scanf("%c %c", o, re);
    scanf("%d", n);
    scanf("%d", r);
    fflush(stdin);
}
int validaDados(char o, char re, int n, int r) {
    if(o != 's' && o != 'S' && o != 'n' && o != 'N') {
        printf(type_sn, "primeiro");
        printf(type_again);
        return 0;
    }
    if(re != 's' && re != 'S' && re != 'n' && re != 'N') {
        printf(type_sn, "segundo");
        printf(type_again);
        return 0;
    }
    if(n < 1 || n > 10) {
        printf(range, "terceiro", 0, 10);
        printf(type_again);
        return 0;
    }
    switch(combinacao(o, re)) {
        case ordem_repete:
        case ordem_nao_repete:
        case nao_ordem_nao_repete:
            if(r < 1 || r > n) {
                printf(range, "quarto", 1, n);
                printf(type_again);
                return 0;
            }
        case nao_ordem_repete:
            if(r < 1) {
                printf(gt, "quarto", 1);
                printf(type_again);
                return 0;
            }
    }
    return 1;
}

int *inicializa(int r) {
    int *num = (int *)malloc(r * sizeof(int));
    for(r-1; r>=0; r--)
        num[r] = 1;

    return num;
}
void incrementa(int *num, int n, int r) {
    int pos = r-1;
    do {
        if(num[pos] == n) {
            num[pos] = 1;
            pos--;
        }
        else {
            num[pos]++;
            return;
        }
    } while(pos >= 0);
}

int repete(int *num, int r) {
    int i, j;
    for(i=0; i<r; i++) {
        for(j=i+1; j<r; j++) {
            if(num[i] == num[j])
                return 1;
        }
    }

    return 0;
}

double numeroReal(int *num, int r) {
    int numReal = 0;
    int i;
    for(i=0; i<r; i++) {
        numReal += num[i] * pow(10, i);
    }

    return numReal;
}

int ordem(int *num, int r) {
    int i, j;
    int menorI; //indice do menor numero
    int aux;
    int *num2 = (int *)malloc(r * sizeof(int));

    for(i=0; i<r; i++) {
        menorI = i;
        for(j=i+1; j<r; j++) {
            if(num[j] < num[menorI])
                menorI = j;
        }
        num2[i] = num[menorI];
    }

    return numeroReal(num2, r) < numeroReal(num, r);
}
//231 ... 123

int numValido(int *num, int r, int tipoCombinacao) {
    int c = tipoCombinacao;

    return  c == ordem_repete
        || (c == ordem_nao_repete && !repete(num, r))
        || (c == nao_ordem_repete && !ordem(num, r))
        || (c == nao_ordem_nao_repete && !repete(num, r) && !ordem(num, r));
}


void imprimeNum(int *num, int r) {
    int i;
    printf("\n---- ");
    for(i=0; i<r; i++)
        printf("%d ", num[i]);
}
void enumera(int tipoCombinacao, double cont, int n, int r) {
    int *num;
    num = inicializa(r);

    for(cont; cont>0; cont--) {
        if(numValido(num, r, tipoCombinacao))
            imprimeNum(num, r);

        incrementa(num, n, r);
    }
}

double fat(int n) {
    double soma = 1;
    for(n; n>0; n--)
        soma *= n;
    return soma;
}
double or(int n, int r) {
    return pow(n, r);
}
double onr(int n, int r) {
    return fat(n)/fat(n-r);
}
double nor(int n, int r) {
    return fat(n+r-1)/(fat(r)*fat(n-1));
}
double nonr(int n, int r) {
    return fat(n)/(fat(r)*fat(n-r));
}


int imprime(int combinacao, int n, int r) {
    double cont;
    char *frase;
    switch(combinacao) {
        case ordem_repete:
            frase = "COM ordem e repeticao";
            cont = or(n, r);
            break;
        case ordem_nao_repete:
            frase = "COM ordem e SEM repeticao";
            cont = onr(n, r);
            break;
        case nao_ordem_repete:
            frase = "SEM ordem e COM repeticao";
            cont = nor(n, r);
            break;
        case nao_ordem_nao_repete:
            frase = "SEM ordem e SEM repeticao";
            cont = nonr(n, r);
            break;
    }

    char *plural = (cont > 1) ? "vezes" : "vez";

    printf(imprime_str, frase, cont, plural);
    enumera(combinacao, or(n,r), n, r);
    return 0;
}

int main() {
    char op;
    do {
        char ordem, repeticao;
        int n, r;

        printf("Entre com os valores <ordem (S|N)> <repeticao (S|N)> <n> <r>: \n");

        do {
            leDados(&ordem, &repeticao, &n, &r);
        }
        while(!validaDados(ordem, repeticao, n, r));

        int c = combinacao(ordem, repeticao);
        imprime(c, n, r);

        printf("\n\nDeseja rodar o programa novamente (S|N)? ");
        scanf("%c", &op);
    } while(op == 's' || op == 'S');

    printf("\n\t Obrigado!\n");
    return 0;
}
