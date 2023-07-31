#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct no{
    int valor;
    struct no *esquerda, *direita;
}NO;    

typedef struct{
    NO *raiz;
    int tamanho;
}ARV;

//nao utilizar muito grande
void inserirEsquerda(NO *no, int item){
    if(no->esquerda == NULL){
        NO *novo=(NO*)malloc(sizeof(NO));
        novo->valor = item;
        novo->esquerda = NULL;
        novo->direita = NULL;
        no->esquerda = novo;
    }
    else{
        if(item < no->esquerda->valor)
            inserirEsquerda(no->esquerda,item);
        if(item > no->esquerda->valor)
            inserirDireita(no->esquerda,item);
    }
}

void inserirDireita(NO *no, int item){
    if(no->direita == NULL){
        NO *novo=(NO*)malloc(sizeof(NO));
        novo->valor = item;
        novo->esquerda = NULL;
        novo->direita = NULL;
        no->direita = novo;
    }
    else{
        if(item > no->direita->valor)
            inserirDireita(no->direita,item);
        if(item < no->direita->valor)
            inserirEsquerda(no->direita,item);
    }
}


void inserir(ARV *l, int item){
    l->tamanho = 0;
    if(l->raiz == NULL){
        NO *novo=(NO*)malloc(sizeof(NO));
        novo->valor = item;
        novo->direita = NULL;
        novo->esquerda = NULL;
        l->raiz = novo;
        l->tamanho++;
    }
    else{
        if(item < l->raiz->valor)
            inserirEsquerda(l->raiz,item);
            l->tamanho++;
        if(item > l->raiz->valor)
            inserirDireita(l->raiz,item);
            l->tamanho++;

    }
    printf("\ntamanho:%d",l->tamanho);
}
//utilizar o inserirNovo nao o inserir normal
NO* inserirNovo(NO *raiz, int item){
    if(raiz == NULL){
        NO *novo=(NO*)malloc(sizeof(NO));
        novo->valor = item;
        novo->direita = NULL;
        novo->esquerda = NULL;
        return novo;
    }else{
        if(item < raiz->valor){
            return raiz->esquerda = inserirNovo(raiz->esquerda,item);
        }
        if(item > raiz->valor){
            return raiz->direita = inserirNovo(raiz->direita,item);
        }
        return raiz;
    }
}

int buscar(NO *raiz,int item){
    if(raiz == NULL){
        return 0;
    }
    else{
        if(raiz->valor == item)
            return 1;
        else{
            if(item < raiz->valor)
                return buscar(raiz->esquerda,item);
            else
                return buscar(raiz->direita,item);
        }

    }
}

NO* removerFolha(NO *raiz, int item){
    if(raiz == NULL){
        printf("item não encontrado");
        return NULL;
    }
    else{
        if(raiz->valor == item){
            if(raiz->esquerda == NULL && raiz->direita == NULL){
                free(raiz);
                return NULL;
            }
            else{
                if(raiz->esquerda == NULL || raiz->direita == NULL){
                    NO *aux;
                    if(raiz->esquerda!=NULL)
                        aux = raiz->esquerda;
                    else
                        aux = raiz->direita;
                    free(raiz);
                    return aux;  
                }
                else{
                    NO *aux = raiz->esquerda;
                    while(aux->direita)
                        aux = aux->direita;
                    raiz->valor = aux->valor;
                    aux->valor = item;  
                    raiz->esquerda = removerFolha(raiz->esquerda,item);
                    return raiz;
                }
            }
        }
        else{
            if(item < raiz->valor)
                raiz->esquerda = removerFolha(raiz->esquerda,item);
            else 
                raiz->direita = removerFolha(raiz->direita,item);
            return raiz;
        }
    }
}

//segundo metodo

int tamanho2(NO *raiz){
    if(raiz==NULL){
        printf("vazia");
        return 0;
    }
    else
        return 1 + (tamanho2(raiz->esquerda)) + (tamanho2(raiz->direita));    

}

void imprimir(NO *raiz){
    if(raiz!=NULL){
        imprimir(raiz->esquerda);
        printf("%d ",raiz->valor); 
        imprimir(raiz->direita);
    }

}

int main(){
    int op, valor;
    ARV arvo;
    //segundo metodo 
    NO *raiz =  NULL;
    //arvo.raiz = NULL;
    do{
        printf("\n0 - sair\n1 - inserir\n2 - imprimir\n3 - buscar");
        scanf("%d",&op);
        switch(op){
            case 0:
                printf("saindo");
                break;
            case 1:
                printf("valor a inserir:");
                scanf("%d",&valor);
                //inserir(&arvo,valor);
                //segundo metodo
                raiz =  inserirNovo(raiz,valor);
                break;
            case 2:
                //imprimir(arvo.raiz);
                //segundo metodo
                imprimir(raiz);
                tamanho2(raiz);
                break;
            //buscar segundo metodo
            case 3:
                printf("qual valor deseja buscar?");
                scanf("%d",&valor);
                printf("resultado:%d",buscar(raiz,valor));
            case 4:
                printf("valor a remover:");
                scanf("%d",&valor);
                raiz =  removerFolha(raiz,valor);
                break;
            default:
                printf("comando invalido");
            
        }
    }
    while(op!=0);

}