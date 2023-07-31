#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct no{
    int valor;
    struct no *proximo;
}No;

typedef struct{
    No *final;
    No *inicio;
    int tam;
}Fila;

void inicializar(Fila *l){
    l->tam = 0;
    l->inicio = NULL;
    l->final = NULL;
}
void inserir(Fila *l, int valor){
    No *novo = malloc(sizeof(No));
    if(novo){
        novo->valor = valor;
        novo->proximo = NULL;
        if(l->inicio == NULL){
            l->inicio = novo;
            l->final = novo;
        }
        else{
            l->final->proximo = novo;
            l->final = novo;
        }
    l->tam++;
    }
}

void inserirPrio(Fila *l, int valor){
    No *novo = malloc(sizeof(No));
    if(novo){
        novo->valor = valor;
        novo->proximo = NULL;
        if(l->inicio == NULL){
            l->inicio = novo;
            l->final = novo;
        }
        else{
            //é prioridade ? (idade maior que 59)
            if(valor>59){
                //é o primeiro na lista de prioridade?
                if(l->inicio->valor<60){
                    novo->proximo = l->inicio;
                    l->inicio = novo;
                }
                else{
                    l->final->proximo = novo;
                    l->final = novo;
                }
            }
            else{
                l->final->proximo = novo;
                l->final = novo;
            }
        }
    l->tam++;
    }
}

void remover(Fila *l){
    No *remover = NULL;
    if(l->tam == 1){
        remover = l->inicio;
        l->inicio = NULL;
        l->final = NULL;
    }
    else{
        remover = l->inicio;
        l->inicio = remover->proximo;
    }
    l->tam--;
    free(remover);
}

void imprimir(Fila *l){
    No *aux = malloc(sizeof(No));
    aux = l->inicio;
    while(aux){
        printf("valores:%d",aux->valor);
        aux = aux->proximo;
    }
}