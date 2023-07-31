#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
//questões 1 e 5
#define MAX 1000

typedef int ITEM;

typedef struct{
    ITEM valor[MAX];
    int tamanho;
} PILHA;

void criar(PILHA *l){
    l->tamanho = 0;
}

void empilhar(PILHA *l, ITEM valo){
    if(l->tamanho==MAX){
        printf("erro");
    }
    else
        l->valor[l->tamanho++] = valo;
    
}

void desempilhar(PILHA *l){
    if(l->tamanho == 0){
        printf("erro ao remover");
    }
    else
        l->tamanho--;
    
}

void imprimirtopo(PILHA *l){
    if(l->tamanho ==0 ){
        printf("erro lista vazia");
    }
    else
        printf("valor do topo:%d",l->valor[l->tamanho-1]);
    

}

bool iguais(PILHA *p1, PILHA *p2){
    int i;
    if(p1->tamanho!=p2->tamanho){
        printf("nao iguais");
    }
    for(i=0;i<p1->tamanho;i++){
            if(p1->valor[i]!=p2->valor[i])
                return false;
    }
    return true;
    
}
int main(){
    PILHA p1;
    criar(&p1);
    empilhar(&p1,12);
    empilhar(&p1,10);
    empilhar(&p1,11);
    imprimirtopo(&p1);
}
//AGORA A VERSÃO PARA DOBRAR O VALOR DO ARRAY
    //typedef struct {
    //ITEM *valor;
    //int tamanho;
//} PILHA;

//void criar(PILHA *l) {
    //l->valor = malloc(MAX * sizeof(ITEM));
    //l->tamanho = 0;
//}

//void empilhar(PILHA *l, ITEM valo) {
    //if (l->tamanho == MAX) {
            // Duplicar o tamanho da pilha
        //int novoTamanho = MAX * 2;
        //ITEM *novoArray = malloc(novoTamanho * sizeof(ITEM));

            // Copiar os elementos do array menor para o novo array
        //for (int i = 0; i < l->tamanho; i++) {
            //novoArray[i] = l->valor[i];
        //}

          // Liberar o array menor (antes de atribuir o novo array)
        //free(l->valor);

            // Atualizar os campos da pilha para refletir a expansão
        //l->valor = novoArray;
        //MAX = novoTamanho;
    //}

        // Empilhar o novo valor
    //l->valor[l->tamanho++] = valo;
//}
//void compactar(PILHA *l) {
  //  int novoTamanho = l->tamanho;

        // Calcula o novo tamanho que comporta os itens atuais
    //while (novoTamanho > MAX / 2) {
      //  novoTamanho /= 2;
    //}

    // Reduz o tamanho da pilha para o novo tamanho calculado
    //ITEM *novoArray = malloc(novoTamanho * sizeof(ITEM));
    //for (int i = 0; i < l->tamanho; i++) {
      //  novoArray[i] = l->valor[i];
    //}

    // Libera o array antigo e atualiza os campos da pilha
    //free(l->valor);
    //l->valor = novoArray;
    //MAX = novoTamanho;
//}
