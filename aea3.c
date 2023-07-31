#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX 1000

typedef int ITEM;

typedef struct{
    ITEM itens[MAX];
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
    l->tamanho = 0;
}


int tamanho(LISTA *l)
{
    return l->tamanho;
}


bool cheia(LISTA *l)
{
    return tamanho(l) == MAX;
}


bool vazia(LISTA *l)
{
    return tamanho(l) == 0;
}


bool inserir(ITEM item, LISTA *l)
{
    if (tamanho(l) == MAX) 
        return false; // lista cheia
    else
       l->itens[l->tamanho++] = item;
    return true;
}


int buscar(ITEM item, LISTA *l)
{
    for (int pos = 0; pos < tamanho(l); pos++)
       if (igual(item, l->itens[pos]))
           return pos; // achou
    return -1; // nao achou
}

int buscarEm(ITEM item,int inicio,int fim, LISTA *l){
    int pos;
    for(pos = inicio;pos<=fim;pos++){
        if(igual(item,l->itens[pos])){
            printf("%d",pos);
            return pos;
        }
    }
    return -1;
}

ITEM enesimo(int n, LISTA *l)
{
    if (n >= 0 && n < tamanho(l))
       return (l->itens[n]);
    else
       exit(EXIT_FAILURE);
}


bool alterar(ITEM item, int pos, LISTA *l)
{
    if (pos >= 0 && pos < tamanho(l))
    {
        l->itens[pos] = item;
        return true;
    } 
    return false;
}


bool inserirNaPos(ITEM item, int i, LISTA *l)
{
    // A posicao tem que estar entre 0 e MAX-1 e ate o tamanho atual
    if ((tamanho(l) >= MAX) || (i < 0) || (i > tamanho(l)))
        return false; // lista cheia ou indice invalido

    // Se for inserido no meio, e necessario abrir espaco para o item
    for (int j = tamanho(l); j > i; j--)
        l->itens[j] = l->itens[j-1];

    // Coloca o item em um espaco vago e ajusta o tamanho        
    l->itens[i] = item;
    l->tamanho++;
    return true;
}




bool remover(ITEM item, LISTA *l)
{
    int i, j;
    for (i = 0; i < tamanho(l); i++)
        if (igual(item, l->itens[i]))
        {
            for (j = i; j < l-> tamanho - 1; j++)
               l->itens[j] = l->itens[j + 1];

            l->tamanho--;
            return true; // achou
        }   
    return false; // nao achou
}

bool removerDaPos(ITEM *item, int i, LISTA *l){

    if ((i < 0) || (i >= tamanho(l)))
        return false; // índice inválido

    *item = l->itens[i];

    for (int j = i; j < tamanho(l)-1; j++)
        l->itens[j] = l->itens[j+1];

    l->tamanho--;
    return true;
}


void exibirItem(ITEM i)
{
    printf("%d", i);
}


void exibirLista(LISTA *l)
{
    printf("[");
    for(int i = 0; i < tamanho(l);)
    {
        exibirItem(l->itens[i++]);
        if (i < tamanho(l))
           printf(",");
    }
    printf("]");
}

void exibirListaReversa(LISTA *l){
  printf("[");
  for(int i = tamanho(l) -1 ;i>=0;i--){
    exibirItem(l->itens[i]);
      if(i < tamanho(l))
        printf(",");
  }
  printf("]");
}

void reversa(LISTA *l){
    int inicio = 0,fim;
    fim = tamanho(l)-1;
    while(inicio<fim){
        int variavel = l->itens[inicio];
        l->itens[inicio] = l->itens[fim];
        l->itens[fim] = variavel;
        inicio++;
        fim--;
    }
    
}

void limpar(LISTA *l)
{
    l->tamanho = 0;
}

void destruir(LISTA *l)
{
   limpar(l);
}

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
	for (int i = 0; i < qtd; i++)
    {
        printf("Digite o valor para a posicao [%d]: ", i);
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
    ITEM item;
    reversa(&l);
    exibirLista(&l);
    getchar();
	return 0;
}