#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct no{
    int valor;
    struct no *proximo;
}No;

typedef struct{
    No *topo;
    int tam;
}Pilha;

void criarpilha(Pilha *l){
    l->tam=0;
    l->topo=NULL;
}

void inserir(Pilha *l,int valor){
    No *novo = malloc(sizeof(No));
    if(novo){
        novo->valor = valor;
        novo->proximo = l->topo; 
        l->topo = novo;
    }
    else
        printf("erro");
    l->tam++;
}

void remover(Pilha *l){
    No *remover = NULL;
    if(l->topo == NULL){
        printf("pilha vazia");
    }
    else{
        remover = l->topo;
        l->topo = remover->proximo;
    }
    l->tam--;
    free(remover);
}

void imprimir(Pilha *l){
    No *aux = l->topo;
    if(l->topo==NULL){
        printf("erro");    
    }
    else{
        while(aux!=NULL){
            printf("%d",aux->valor);
            aux = aux->proximo;
        }
    }
}

int main(){
    Pilha *p1 = (Pilha*)malloc(sizeof(No));
    criarpilha(p1);
    inserir(p1,10);
    inserir(p1,12);
    inserir(p1,13);
    imprimir(p1);
    return 0;
}