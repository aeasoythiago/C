#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX 1000

typedef int ITEM;

typedef struct{
    ITEM valor[MAX];
    int fim;
}FILA;

void inicializar(FILA *l){
    l->fim = 0;
}

void inserir(FILA *l, ITEM num){
    if(l->fim == MAX){
        printf("cheia");
    }
    else{
        l->valor[l->fim] = num;
        l->fim++;
    }
}

int remover(FILA *l){
    int dado;
    if(l->fim ==0){
        printf("vazia");
    }
    else{
        dado=l->valor[0];
        for(int i=0;i<l->fim;i++){
            l->valor[i] = l->valor[i+1];
        }
        l->fim--;
        return dado;
    }
}

void imprimir(FILA *l){
    int i;
    printf("imprimindo os valores:\n");
    for(i=0;i<l->fim;i++){
        printf("%d ",l->valor[i]);
    }
}

int main(){
    FILA f1;
    inicializar(&f1);
    inserir(&f1,10);
    inserir(&f1,111);
    inserir(&f1,12);
    remover(&f1);
    imprimir(&f1);
}

