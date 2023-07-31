#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#ifndef LISTA_SEQ_ORDENADA
#define LISTA_SEQ_ORDENADA

#define MAX 1000000

typedef int ITEM;

typedef struct{
    ITEM itens[MAX];
    int tamanho;
} LISTA;

/*
   Compara o item x com o y, retornando:
     1 caso x > y
     0 caso x = y
    -1 caso x < y
*/
char compare(ITEM x, ITEM y);

// Retorna true se x = y e false caso contrario
bool igual(ITEM x, ITEM y);

// Inicializa a lista deixando-a pronta para ser utilizada.
void inicializar(LISTA *l);

// Retornar o tamanho da lista sequencial
int tamanho(LISTA *l);

// Retorna true se a lista esta cheia (Tamanho = MAX)
bool cheia(LISTA *l);

// Retorna true se a lista esta vazia (Tamanho = 0)
bool vazia(LISTA *l);

/* 
  Objetivo: Insere o item passado como parametro na lista passada.
            Se o tamanho da lista ja for igual ao tamanho maximo,
            a funcao Inserir retorna false.
*/
bool inserir(ITEM item, LISTA *l);

/*
  Objetivo: Busca na lista o item passado.
            Caso encontre, retorna a posicao (entre 0 e tamanho - 1).
            Caso nao encontre, retorna o valor -1.
*/
int buscar(ITEM item, LISTA *l);

// Retornar o n-esimo elemento da lista sequencial
// Pre-condicao: 0 <= n < tamanho
ITEM enesimo(int n, LISTA *l);

/*
  Objetivo: Remove o item passado da lista. Caso nao seja
            encontrato, retorna false. Se for removido, true.
*/
bool remover(ITEM item, LISTA *l);

// Exibicao de um item da lista
void exibirItem(ITEM i);

// Exibicao da lista sequencial
void exibirLista(LISTA *l);

// Remove todos os valores da lista, deixando-a vazia
void limpar(LISTA *l);

// Destruicao da lista sequencial
void destruir(LISTA *l);

#endif // LISTA_SEQ_ORDENADA

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


ITEM enesimo(int n, LISTA *l)
{
    if (n >= 0 && n < tamanho(l))
       return (l->itens[n]);
    else
       exit(EXIT_FAILURE);
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


void limpar(LISTA *l)
{
    l->tamanho = 0;
}


void destruir(LISTA *l)
{
    limpar(l);
}

//////////////// MUDANCAS SOBRE A LISTA SEQUENCIAL ////////////////


/*
 Objetivo: Move para uma posicao para esquerda todos os elementos
           a direita da posicao pos.
*/ 
void moverParaEsquerda(int pos, LISTA *l)
{
    for (; pos < l-> tamanho - 1; pos++)
        l->itens[pos] = l->itens[pos + 1];
}


/*
 Objetivo: Move para uma posicao para direita todos os elementos a partir
           da posicao pos, comecando a copia da posicao tamanho - 1 (final)
           para tamanho e terminando ate chegar a copiar para pos + 1 o
           item contido em pos.
*/ 
void moverParaDireita(int pos, LISTA *l)
{
    for (int i = l->tamanho; i > pos; i--)
        l->itens[i] = l->itens[i-1];
}


/*
  Objetivo: Executa uma busca binaria na lista. 
            Depende da lista estar ordenada.
            Retorna a posicao (indice) do item (no) passado como 
            parametro na lista.
            Caso nao encontre, retorna o valor -1.
*/
int buscaBin(ITEM item, int inicio, int fim, ITEM *itens)
{
    int pos;
    printf("Comecando BuscaBin Inicio: %d, Fim: %d\n", inicio, fim);
    while (inicio <= fim)
    {
        int meio = (inicio + fim) / 2; // calcula a posicao do meio
        printf("Meio: %d, Inicio: %d, Fim: %d\n", meio, inicio, fim);
        int comp = compare(item, itens[meio]);
        if (comp == 0){
            pos = meio - 1; // iguais 
            return pos;
        }    // achou
        else
        {
            if (comp == 1) // item maior do que o do meio
                inicio = meio + 1; // concentra a busca na parte da direita
            else // item menor do que o do meio 
                fim = meio - 1; // concentra a busca na parte da esquerda
        }
    }
    return -1; // nao achou
}


/*
  Objetivo: Executa uma busca binaria na lista (de forma recursiva). 
            Depende da lista estar ordenada.
            Recebe como parametro as posicoes de inicio (inf) e 
            fim (sup) da busca.
            Retorna a posicao (indice) do item (no) passado como 
            parametro na lista.
            Caso nao encontre, retorna o valor -1.
*/
int buscaBinRec(ITEM item, int inicio, int fim, ITEM *itens)
{
    if (inicio <= fim)
    {
        int meio = (inicio + fim) / 2;
        int comp = compare(item, itens[meio]);
        if (comp == 0) 
            return meio; // achou
        else
        {
            if (comp == 1) // item maior do que o do meio 
                return buscaBinRec(item, meio + 1, fim, itens); // concentra a busca na parte da direita
            else  // item menor do que o do meio 
                return buscaBinRec(item, inicio, meio - 1, itens); // concentra a busca na parte da esquerda
        }
    }
    return -1; // nao achou
}


int buscar(ITEM item, LISTA *l)
{
    printf("Tamanho da lista: %d\n", tamanho(l));
    //return buscaBin(item, 0, tamanho(l) - 1, l->itens);
    return buscaBinRec(item, 0, tamanho(l) - 1, l->itens);
}

int buscarEm(ITEM item,int inicio,int fim, LISTA *l){
    int pos;
    for(pos = inicio;pos<fim;pos++){
        if(buscaBin){
            printf("%d",pos);
            return pos;
        }
    }
    return -1;

}


/*
 Objetivo: Inserir em uma lista ordenada o item passado e garantir
           que nao havera duplicacao. 
           Esta versao nao usa a busca sequencial (menos eficiente).
*/
bool inserir(ITEM item, LISTA *l){
    if (cheia(l)) 
        return false; // lista cheia
    
    int i = 0;

    // Faz uma busca sequencial ate o ponto correto de insercao
    // ou chegar ao final da lista
    while (i < tamanho(l) && (compare(l->itens[i], item) == -1)) i++;
    
    if (i == tamanho(l)) // inserindo no final da lista
        return inserirNaPos(item, i, l);
    else 
    {
       if (igual(l->itens[i], item)) // Se encontrou o item, evita incluir um duplicado
          return false;
       else 
          inserirNaPos(item, i, l);
          return buscaBin;
    } 
}

/*
  Objetivo: Remove o item que  coincide com o parametro item
            passado. Caso nao seja encontrado o item, retorna
            false. Se o item foi removido, retorna true.
*/
bool remover(ITEM item, LISTA *l)
{
    int pos = buscar(item, l);
    if (pos == -1)
        return false; // nao achou
    else
    {
        moverParaEsquerda(pos, l);
        l->tamanho--;
        return true; // achou
    }
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
    for (int i = 1; i <= qtd; i++)
    {
        printf("Digite o valor %d/%d: ", i, qtd);
        scanf("%d", &item);
        inserir(item, l);
	}

	imprimirStatus(l);
}


// Testa a insercao de valores na lista escolhendo a posicao
void testarInserirVarios(LISTA *l)
{ 
    
    printf("=> Teste de InserirVarios\n");
    int qtd;
    printf("Quantos itens aleatorios deseja inserir na lista? ");
    scanf("%d", &qtd);

	ITEM item;
    int sucessos = 0;
    int erros = 0;

    // Inicia a contagem de tempo
    time_t inicio = time(NULL);
	for (int i = 0; i < qtd; i++)
    {
        item = rand();
        if (inserir(item, l))
            sucessos += 1;
        else
            erros += 1;
	}
    // Finaliza a contagem de tempo
    time_t fim = time(NULL);
    // Calcula o tempo decorrido
    double tempo_gasto = (double)(fim - inicio);
    // Tempo medio por insercao
    double tempo_medio = 1000.0  * tempo_gasto / qtd;

    printf("Insercoes com sucesso: %d\n", sucessos);
    printf("Insercoes com erro: %d\n", erros);
    printf("Tempo total das insercoes %f segundos\n", tempo_gasto);
    printf("Tempo medio por insercao %f milisegundos\n", tempo_medio);
}

void clonar(LISTA *l, LISTA *C){
    while (l)
    {
        inserir(l->itens,C);
    }
    
}

// Testa a busca de valores na lista
void testarBuscar(LISTA *l)
{
    // Testa a busca por um valor existente
    printf("=> Teste de Busca\n");

    // Preenchendo a lista com valores crescentes
    int TOTAL = 100;
    limpar(l);
    printf("=> Limpando a lista\n");

    // Preenchendo a lista com os valores de TOTAL ate 1
    for (int i = TOTAL; i > 0; i--)
    {
        if (!inserir(i, l))
            printf("Algum erro duranta a insercao do valor %d\n", i);
        else
           printf("Inserido o valor %d\n", i);
    }
       
    printf("=> Preenchida a lista com valores de 1 a %d\n", TOTAL);
        
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


/////////////////////////////////////////////////////

int main(){
	LISTA l;
	
	inicializar(&l);
    testarInserir(&l);
    testarInserirVarios(&l);
    testarBuscar(&l);   
    limpar(&l);
    imprimirStatus(&l);
    destruir(&l);
    
    getchar();
	return 0;
}