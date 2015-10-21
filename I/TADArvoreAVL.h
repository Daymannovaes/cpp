typedef struct NoArvore* ArvoreAVL;

struct NoArvore{ //cria uma estrutura No
    int valor;
    int altura;
    struct NoArvore *esquerda;
    struct NoArvore *direita;
};

ArvoreAVL* cria_ArvoreAVL(){ //aloca dinamicamente o espacao de memoria necessario para criacao da arvore
    ArvoreAVL* raiz = (ArvoreAVL*) malloc(sizeof(ArvoreAVL));
    if(raiz != NULL)
        *raiz = NULL;
    return raiz;
}

int altura_NoArvore(struct NoArvore* NoArvore){ //verifica qual e' a altura do no e se e' necessario fazer o balanceamento
    if(NoArvore == NULL)
        return -1;
    else
    return NoArvore->altura;
}

int fatorBalanceamento_NoArvore(struct NoArvore* NoArvore){ //calcula o fator de balanceamento do no
    return labs(altura_NoArvore(NoArvore->esquerda) - altura_NoArvore(NoArvore->direita));
}

int verifica_maior(int x, int y){//verifica qual o maior valor para posicionar de forma correta na arvore
    if(x > y)
        return x;
    else
        return y;
}

int altura_ArvoreAVL(ArvoreAVL *raiz){ //calcula a altura da arvore
    if (raiz == NULL)
        return 0;
    if (*raiz == NULL)
        return 0;
    int alt_esquerda = altura_ArvoreAVL(&((*raiz)->esquerda));
    int alt_direita = altura_ArvoreAVL(&((*raiz)->direita));
    if (alt_esquerda > alt_direita)
        return (alt_esquerda + 1);
    else
        return(alt_direita + 1);
}

void imprime_ArvoreAVL(ArvoreAVL *raiz){ //imprime a arvore avl inserida
    if(raiz == NULL)
        return;
    if(*raiz != NULL){
        imprime_ArvoreAVL(&((*raiz)->esquerda));
        //printf("%d\n",(*raiz)->valor);
        printf("No da Arvore: %03d | Altura:(%d) | Fator de Balanceamento:(%d)\n",(*raiz)->valor,altura_NoArvore(*raiz),fatorBalanceamento_NoArvore(*raiz));
        imprime_ArvoreAVL(&((*raiz)->direita));
    }
}

void RotacaoSimplesDireita(ArvoreAVL *A){ //faz rotacao para direita para balancear a arvore
    struct NoArvore *B;
    B = (*A)->esquerda;
    (*A)->esquerda = B->direita;
    B->direita = *A;
    (*A)->altura = verifica_maior(altura_NoArvore((*A)->esquerda),altura_NoArvore((*A)->direita)) + 1;
    B->altura = verifica_maior(altura_NoArvore(B->esquerda),(*A)->altura) + 1;
    *A = B;
}

void RotacaoSimplesEsquerda(ArvoreAVL *A){//faz rotacao para esquerda para balancear a arvore
    struct NoArvore *B;
    B = (*A)->direita;
    (*A)->direita = B->esquerda;
    B->esquerda = (*A);
    (*A)->altura = verifica_maior(altura_NoArvore((*A)->esquerda),altura_NoArvore((*A)->direita)) + 1;
    B->altura = verifica_maior(altura_NoArvore(B->direita),(*A)->altura) + 1;
    (*A) = B;
}

void RotacaoDuplaDireita(ArvoreAVL *A){//faz rotacao dupla para direita para balancear a arvore
    RotacaoSimplesEsquerda(&(*A)->esquerda);
    RotacaoSimplesDireita(A);
}

void RotacaoDuplaEsquerda(ArvoreAVL *A){//faz rotacao dupla para esquerda para balancear a arvore
    RotacaoSimplesDireita(&(*A)->direita);
    RotacaoSimplesEsquerda(A);
}

int insere_ArvoreAVL(ArvoreAVL *raiz, int valor){ //insere nos na arvore
    int res;
    if(*raiz == NULL){
        struct NoArvore *novo;
        novo = (struct NoArvore*)malloc(sizeof(struct NoArvore));
        if(novo == NULL)
            return 0;

        novo->valor = valor;
        novo->altura = 0;
        novo->esquerda = NULL;
        novo->direita = NULL;
        *raiz = novo;
        return 1;
    }

    struct NoArvore *atual = *raiz;
    if(valor < atual->valor){
        if((res = insere_ArvoreAVL(&(atual->esquerda), valor)) == 1){
            if(fatorBalanceamento_NoArvore(atual) >= 2){
                if(valor < (*raiz)->esquerda->valor ){
                    RotacaoSimplesEsquerda(raiz);
                }else{
                    RotacaoDuplaDireita(raiz);
                }
            }
        }
    }else{
        if(valor > atual->valor){
            if((res = insere_ArvoreAVL(&(atual->direita), valor)) == 1){
                if(fatorBalanceamento_NoArvore(atual) >= 2){
                    if((*raiz)->direita->valor < valor){
                        RotacaoSimplesEsquerda(raiz);
                    }else{
                        RotacaoDuplaEsquerda(raiz);
                    }
                }
            }
        }
        else
            return 0;
    }

    atual->altura = verifica_maior(altura_NoArvore(atual->esquerda),altura_NoArvore(atual->direita)) + 1;

    return res;
}

//DEFINE QUAL O FILHO DE MENOR VALOR DA ARVORE DA direitaEITA
struct NoArvoreArvore* procuraMenor(struct NoArvore* atual){
    struct NoArvore *NoArvore1 = atual;
    struct NoArvore *NoArvore2 = atual->esquerda;
    while(NoArvore2 != NULL){
        NoArvore1 = NoArvore2;
        NoArvore2 = NoArvore2->esquerda;
    }
    return NoArvore1;
}

//REMOVE ELEMENTO DA ARVORE AVL
int remove_ArvAVL(ArvAVL *raiz, int valor){
	if(*raiz == NULL){// valor não existe
	    printf("valor não existe!!\n");
	    return 0;
	}

    int res;
	if(valor < (*raiz)->info){
	    if((res = remove_ArvAVL(&(*raiz)->esquerda,valor)) == 1){
            if(fatorBalanceamento_NoArvore(*raiz) >= 2){
                if(alt_NoArvore((*raiz)->direita->esquerda) <= alt_NoArvore((*raiz)->direita->direita))
                    RotacaoSimplesDireita(raiz);
                else
                    RotacaoDuplaEsquerda(raiz);
            }
	    }
	}

	if((*raiz)->info < valor){
	    if((res = remove_ArvAVL(&(*raiz)->direita, valor)) == 1){
            if(fatorBalanceamento_NoArvore(*raiz) >= 2){
                if(alt_NoArvore((*raiz)->esquerda->direita) <= alt_NoArvore((*raiz)->esquerda->esquerda) )
                    RotacaoSimplesDireita(raiz);
                else
                    RotacaoLR(raiz);
            }
	    }
	}

	if((*raiz)->info == valor){
	    if(((*raiz)->esquerda == NULL || (*raiz)->direita == NULL)){// nó tem 1 filho ou nenhum
			struct NoArvore *oldNoArvorede = (*raiz);
			if((*raiz)->esquerda != NULL)
                *raiz = (*raiz)->esquerda;
            else
                *raiz = (*raiz)->direita;
			free(oldNoArvorede);
		}else { // nó tem 2 filhos
			struct NoArvore* temp = procuraMenor((*raiz)->direita);
			(*raiz)->info = temp->info;
			remove_ArvAVL(&(*raiz)->direita, (*raiz)->info);
            if(fatorBalanceamento_NoArvore(*raiz) >= 2){
				if(alt_NoArvore((*raiz)->esquerda->direita) <= alt_NoArvore((*raiz)->esquerda->esquerda))
					RotacaoLL(raiz);
				else
					RotacaoLR(raiz);
			}
		}
		if (*raiz != NULL)
            (*raiz)->alt = maior(alt_NoArvore((*raiz)->esquerda),alt_NoArvore((*raiz)->direita)) + 1;
		return 1;
	}

	(*raiz)->alt = maior(alt_NoArvore((*raiz)->esquerda),alt_NoArvore((*raiz)->direita)) + 1;

	return res;
}
