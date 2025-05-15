#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct pessoa{
    struct pessoa *prox;
    int senha;
    char nome[50];
}pessoa;

typedef struct fila{
    int tamanho;
    pessoa *inicio;
    pessoa *fim;
}fila;

void inicializar(fila *f){
    f->tamanho = 0;
    f->inicio = NULL;
    f->fim = NULL;
}

void inserir(fila *f,char nome1[],int senha1){
    if(senha1<=0){
        printf("Senha invalida.Deve ser maior que 0\n");
        return;
    }
    pessoa *ponteiro = (pessoa*)malloc(sizeof(pessoa));
    if(ponteiro){
        ponteiro->prox = NULL;
        strcpy(ponteiro->nome,nome1);
        ponteiro->senha = senha1;
        if(f->inicio == NULL){
            f->inicio = ponteiro;
            f->fim = ponteiro;
        }
        else{
            f->fim->prox = ponteiro;
            f->fim = ponteiro;
          
        }
        f->tamanho++;
    }
    else{
        printf("Memória nao alocada\n");
    }
}

void remover(fila *f){
    if(f->inicio == NULL){
        printf("fila vazia\n");
    }
    else{
        pessoa *remove = f->inicio;
        f->inicio = f->inicio->prox;
        f->tamanho--;
        printf("Removida.\nNome:%s\tSenha:%d\n",remove->nome,remove->senha);
        free(remove);
    }
    if(f->inicio == NULL){
        f->fim = NULL;
    }
}

void imprimir(fila *f){
    if(f->inicio == NULL){
        printf("Fila vazia...\n");
    }
    pessoa *ponteiro = f->inicio;
    while (ponteiro != NULL)
    {
        printf("Nome: %s\tSenha: %d\n",ponteiro->nome,ponteiro->senha);
        ponteiro = ponteiro->prox;
    }
}

void salvarbin(fila *f){
    FILE *arquivo = fopen("PROJETO3.txt","wb");
    if(arquivo){
        fwrite(&f->tamanho,sizeof(int),1,arquivo);
        pessoa *ponteiro = f->inicio;
        while(ponteiro!= NULL){
            fwrite(ponteiro->nome,sizeof(char),50,arquivo);
            fwrite(&ponteiro->senha,sizeof(int),1,arquivo);
            ponteiro = ponteiro->prox;
        }
        fclose(arquivo);
    }
    else{
        printf("Arquivo nao salvo...\n");
    }
}

void lerbin(fila *f){
    FILE *arquivo = fopen("PROJETO3.txt","rb");
    if(arquivo){
        inicializar(f);
        int qtd;
        fread(&qtd, sizeof(int), 1, arquivo);
        for(int i = 0; i < qtd; i++){
            pessoa *nova = (pessoa *)malloc(sizeof(pessoa));
            if(nova == NULL){
                printf("Erro de memória\n");
                fclose(arquivo);
                return;
            }
            fread(nova->nome, sizeof(char), 50, arquivo);
            fread(&nova->senha, sizeof(int), 1, arquivo);
            nova->prox = NULL;

            if(f->inicio == NULL){
                f->inicio = nova;
                f->fim = nova;
            } else {
                f->fim->prox = nova;
                f->fim = nova;
            }
            f->tamanho++;
        }
        fclose(arquivo);
    } else {
        printf("Arquivo nao encontrado\n");
    }
}


int main(){
    int op,senha1;
    char nome1[50];
    fila *f = (fila*)malloc(sizeof(fila));
    if(f == NULL){
        printf("Erro ao alocar memoria.\n");
        return 1;
    }
    inicializar(f);
    do
    {
        printf("======Fila de atendimento=====\n");
        printf("1.Inserir na fila\n2.Atender pessoa\n3.Imprimir fila\n4.Salvar em arquivo\n5.Ler arquivo\n0.Sair");
        scanf("%d",&op);
        getchar();
        switch (op)
        {
        case 1:
            printf("Digite o nome da pessoa:\n");
            fgets(nome1,50,stdin);
            nome1[strcspn(nome1, "\n")] = 0;
            printf("Digite a senha da pessoa:\n");
            scanf("%d",&senha1);
            inserir(f,nome1,senha1);
            break;
        case 2:
            remover(f);
            break;
        case 3:
            imprimir(f);
            break;
        case 4:
            salvarbin(f);
            printf("Arquivo salvo com sucesso.\n");
            break;
        case 5:
            lerbin(f);
            printf("Arquivo lido com sucesso.\n");
            break;
        case 0:
            printf("Saindo...\n");
            break;
        default:
            printf("Opcao invalida...\n");
            break;
        }
    } while (op != 0);
    
}
