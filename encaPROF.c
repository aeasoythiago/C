#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef int ITEM;

typedef struct estrutura
{
    ITEM item;
    struct estrutura *prox;
} NO;

typedef struct
{
    NO* cabeca;
    int tamanho;
} LISTA;

char compare(ITEM x, ITEM y)
{
    return x > y ? 1 : (x < y ? -1 : 0);
}


bool igual(ITEM x, ITEM y)
{
    return compare(x,y) == 0;
}


void inicializar(LISTA *l)
{
    l->cabeca = NULL;
    l->tamanho = 0;
}


NO* criarNo(ITEM item, NO *prox)
{
    NO* pNovo = (NO*) malloc(sizeof(NO));
    if (pNovo == NULL)
    {
        printf("Nao foi possivel alocar memoria para pNovo\n");
        exit(EXIT_FAILURE);        
    }
    pNovo->item = item;
    pNovo->prox = prox;
    return pNovo;
}


int tamanho(LISTA *l)
{
    return l->tamanho;
}


bool cheia(LISTA *l)
{
    return false;
}


bool vazia(LISTA *l)
{
    return l->cabeca == NULL;
}


bool inserir(ITEM item, LISTA *l){
    l->cabeca = criarNo(item, l->cabeca);
    l->tamanho++;
    return true;
}


/*
    Objetivo: Retorna o endereco do No contido na posicao informada.
              Caso a posicao seja invalida (negativa ou maior ou igual
              ao tamanho da lista, retorna NULL.
*/
NO* noNaPosicao(int n, LISTA *l)
{
    if (n < 0 || n >= tamanho(l))
        return NULL;
    
    NO* p = l->cabeca;
    for (int i = 0; i < n; i++)
        p = p->prox;
    return p;  // existe um n-esimo e p aponta para ele
}


int buscar(ITEM item, LISTA *l)
{
    NO* p = l->cabeca;
    int pos = 0;
    while (p)   // p != NULL        
    {
        if (igual(item, p->item))
            return pos;
        p = p->prox;
        pos++;
    }
    return -1; // Nao achou
}


ITEM enesimo(int n, LISTA *l) {
    NO * no = noNaPosicao(n, l);
    if (no)
        return no->item;
    else
    {
        printf("Posicao inexistente na lista (%d)\n", n);
        exit(EXIT_FAILURE);
    }
}


bool alterar(ITEM item, int pos, LISTA *l)
{
    NO * no = noNaPosicao(pos, l);
    if (no)
    {
        no->item = item;  // existe um n-esimo e p aponta para ele
        return true; 
    }
    else
        return false;
}


bool inserirNaPos(ITEM item, int i, LISTA *l)
{
    if (i < 0 || i > tamanho(l))
    {
        printf("Posicao de insercao invalida (%d)\n", i);
        exit(EXIT_FAILURE);
    }
    
    if (i == 0) // insercao na cabeca da lista
    {
        l->cabeca = criarNo(item, l->cabeca);
    }
    else // insercao no meio ou final
    {
        NO* pAnterior = noNaPosicao(i-1, l);
        pAnterior->prox = criarNo(item, pAnterior->prox);
    }
    l->tamanho++;
    return true;
}
//atividae 1
void ins_f(LISTA *l, int num){
    NO *no,*novo = malloc(sizeof(NO));
    if(novo){
        novo->item = num;
        novo->prox = NULL;
        if(l->tamanho == 0){
            l->cabeca = novo;
        }
        else{
            no = l->cabeca;
            while(no->prox != NULL)
                no = no->prox;
            no->prox = novo;
        }
    }
        l->tamanho++;
}
//atividade 2
bool removerDaPos(ITEM *item,int i, LISTA *l){
    NO *no, *remover = NULL;
    if(l->tamanho >= i){
        if(l->cabeca->item == item){
            remover = l->cabeca;
            l->cabeca = remover->prox;
            l->tamanho--;
            return true;
        }   
        else{
            no = l->cabeca;
            for(int n = 1;n<i;n++){
                no = no->prox;
            }
            remover = no->prox;
            no->prox = remover->prox;
            l->tamanho--;
            return true;
        }
    }
    else
        return false;
    
}
//atividade 3
LISTA * clonar(LISTA *l){
    LISTA* nova_lista = (LISTA*)malloc(sizeof(LISTA));
    if(nova_lista == NULL){
        printf("erro ao alocar memoria");
        return NULL;
    }
    inicializar(nova_lista);

    NO *no = l->cabeca;
    while(no->prox != NULL){
        inserir(no->item,nova_lista);
        no = no->prox;
        nova_lista->tamanho++;
    }
    return nova_lista;
}


bool remover(ITEM item, LISTA *l)
{
   if (vazia(l))
      return false;

   NO* pAnterior = l->cabeca;

   if (igual(item, l->cabeca->item))
   {
       // Remove o item da cabeca da lista e a cabeca passa a ser
       // item seguinte ao removido
       l->cabeca = l->cabeca->prox;
       l->tamanho--;
       free(pAnterior);
       return true;
   }
   else
   { 
      // Percorre a lista ate encontrar o item procurado.
      // Remove o item e corrige o apontador prox do NO anterior para
      // apontar para o proximo NO do item sendo removido
      while (pAnterior->prox)  // prox != NULL
      {
         NO* pAtual = pAnterior->prox;

         if (igual(item, pAtual->item))
         { 
            pAnterior->prox = pAtual->prox;
            free(pAtual);
            l->tamanho--;
            return true;
         }

         pAnterior = pAtual;
      }
    }
    return false; // Nao removeu
}


void exibirItem(ITEM i)
{
    printf("%d", i);
}


void exibirLista(LISTA *l)
{
    printf("[");
    NO* p = l->cabeca;
    while (p)  // p != NULL
    {
        exibirItem(p->item);
        if (p->prox)
           printf(",");
        p = p->prox;
    }
    printf("]");
}

void limpar(LISTA *l)
{
    NO* atual = l->cabeca;
    while (atual) {
        NO* prox = atual->prox; // guarda proxima posicao
        free(atual);            // libera memoria apontada por atual
        atual = prox;
    }
    l->cabeca = NULL; // ajusta inicio da lista (vazia)
    l->tamanho = 0;
}

void destruir(LISTA *l)
{
    limpar(l);
}

// Imprime na tela o status da lista
void imprimirStatus(LISTA *l)
{
    printf("Tamanho = %d\n", tamanho(l));
	exibirLista(l);
	printf("\n");
}

// Testa a insercao de valores na lista
void testarInserir(LISTA *l)
{
    printf("=> Teste de Inserir\n");
    int qtd;
    printf("Quantos itens deseja guardar na lista? ");
    scanf("%d", &qtd);

    ITEM item;
	for (int i = 1; i <= qtd; i++)
    {
        printf("Digite o valor %d/%d: ", i, qtd);
        scanf("%d", &item);
        inserir(item, l);
	}

	imprimirStatus(l);
}

// Testa a insercao de valores na lista escolhendo a posicao
void testarInserirNaPos(LISTA *l)
{
    printf("=> Teste de InserirNaPos\n");
    int qtd;
    printf("Quantos itens deseja inserir na lista? ");
    scanf("%d", &qtd);

	ITEM item;
	for (int i = 0; i < qtd; i++)
    {
        printf("Digite a posicao de insercao (de 0 a %d): ", tamanho(l));
        int p;
        scanf("%d", &p);
  
        printf("Digite o valor para a posicao [%d]: ", p);
        scanf("%d", &item);
        if (inserirNaPos(item, p, l))
            printf("Insercao com sucesso\n");
        else
            printf("Erro na insercao\n");

        imprimirStatus(l);
	}

}
// Testa a busca de valores na lista
void testarBuscar(LISTA *l)
{
   // Testa a busca por um valor existente
    printf("=> Teste de Busca\n");
    printf("Digite o valor que deseja buscar: ");
    ITEM item;
    scanf("%d", &item);
    int pos = buscar(item, l); 
    if (pos >= 0)
        printf("Achou na posicao: %d\n", pos);
    else
        printf("Nao achou o item na lista\n");

    // Testa a busca por uma posicao existente
    printf("Digite a posicao que deseja acessar (ou -1 para sair): ");
    int p;
    scanf("%d", &p);
    while (p != -1)
    {
        ITEM item = enesimo(p, l);
        printf("Achou na posicao[%d] o valor: %d\n", p, item);
        // Leitura da proxima posicao a ser acessada
        printf("Digite a posicao que deseja acessar (ou -1 para sair): ");
        scanf("%d", &p);
    }

}

// Testa a alteracao de um valor numa posicao
void testarAlterar(LISTA *l)
{
    printf("=> Teste da Alteracao\n");
    int p;
    printf("Digite a posicao que deseja alterar (ou -1 para sair): ");
    scanf("%d", &p);
    while (p != -1)
    {
        // Leitura do novo valor
        printf("Digite o NOVO valor para a posicao [%d]: ", p);
        ITEM item;
        scanf("%d", &item);
        if (alterar(item, p, l))
           printf("Alterou com sucesso\n");
        else
           printf("Erro na alteracao\n");

        imprimirStatus(l);

        // Leitura da proxima posicao a ser acessada
        printf("Digite a posicao que deseja alterar (ou -1 para sair): ");
        scanf("%d", &p);
    }
}

/////////////////////////////////////////////////////

int main(){
	LISTA l;
	
	inicializar(&l);
    testarInserir(&l);
    testarInserirNaPos(&l);
    testarBuscar(&l);   
    testarAlterar(&l);
    destruir(&l);
    imprimirStatus(&l);
        
    getchar();
	return 0;
}
