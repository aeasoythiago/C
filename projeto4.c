#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct transacao {
    float valor;
    char tipo[10];
    struct transacao *prox;
} transacao;

typedef struct usuario {
    char nome[50];
    char senha[20];
    float saldo;
    transacao *extrato; 
    struct usuario *prox;
} usuario;

void criarusuario(usuario **u, char nome1[],char senha1[], float saldo1){
    if(saldo1 < 0){
        return;
    }
    usuario *novousuario = (usuario*)malloc(sizeof(usuario));
    if(novousuario == NULL){
        printf("Erro ao alocar memória...\n");
    }
    strcpy(novousuario->nome,nome1);
    strcpy(novousuario->senha,senha1);
    novousuario->saldo = saldo1;
    novousuario->extrato = NULL;
    novousuario->prox = *u;
    *u = novousuario;
}

usuario* login(usuario *u, char nome1[], char senha1[]) {
    while (u != NULL) {
        if (strcmp(u->nome, nome1) == 0 && strcmp(u->senha, senha1) == 0) {
            return u; 
        }
        u = u->prox;
    }
    if(u == NULL){
        printf("Usuário não cadastrado.\n");
    }
    return NULL; 
}

void deposito(usuario *u, char nome1[], char senha1[], float valor1){
    usuario *logado = login(u,nome1,senha1);
    if(logado){
        logado->saldo += valor1;
        transacao *nova = (transacao*)malloc(sizeof(transacao));
        if(nova){
            nova->valor = valor1;
            strcpy(nova->tipo,"Deposito");
            nova->prox = logado->extrato;
            logado->extrato = nova;
            printf("Deposito realizado com sucesso.\n");
        }
        else
            printf("Erro ao realizar ação.\n");
    }
    else
        printf("Usuário ou senha incorretos.\n");
}

void saque(usuario *u, char nome1[], char senha1[], float valor1){
    usuario *logado = login(u,nome1,senha1);
    if(logado){
        if(valor1 > logado->saldo){
            printf("Saldo insuficiente.\n");
            return;
        }
        
        transacao *nova = (transacao*)malloc(sizeof(transacao));
        if(nova){
            nova->valor = valor1;
            strcpy(nova->tipo,"Saque");
            nova->prox = logado->extrato;
            logado->extrato = nova;
        
            logado->saldo -= valor1;
            printf("Saldo sacado com sucesso.\n");
        }
        else
            printf("Erro ao realizar ação.");
    }
    else{
        printf("Usuário ou senha incorretos.\n");
    }
}

void consultarsaldo(usuario *u, char nome1[], char senha1[]) {
    usuario *logado = login(u, nome1, senha1);
    if (logado != NULL) {
        printf("Saldo disponível: R$ %.2f\n", logado->saldo);
    } else {
        printf("Usuário ou senha incorretos.\n");
    }
}

void salvarExtrato(usuario *u) {
    if(u == NULL){
        printf("Nenhum usuário cadastrado. Nada para salvar.\n");
    }
    FILE *arquivo = fopen("extrato.txt", "w");
    if (!arquivo) {
        printf("Erro ao abrir arquivo!\n");
        return;
    }

    while (u != NULL) {
        fprintf(arquivo, "Usuário: %s\n", u->nome);
        transacao *t = u->extrato;
        while (t != NULL) {
            fprintf(arquivo, "%s: %.2f\n", t->tipo, t->valor);
            t = t->prox;
        }
        fprintf(arquivo, "\n");
        u = u->prox;
    }

    fclose(arquivo);
    printf("Extrato salvo.\n");
}

void lerExtratoArquivo() {
    FILE *arquivo = fopen("extrato.txt", "r");
    if (!arquivo) {
        printf("Erro ao abrir arquivo!\n");
        return;
    }

    char linha[100];
    int encontrado = 0;
    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        printf("%s", linha);
        encontrado = 1;
    }
    if(encontrado == 1){
        printf("Arquivo lido com sucesso.\n");
    }
    else
        printf("Arquivo não encontrado para ser lido.\n");
    fclose(arquivo);
}

usuario* mandar(usuario *u, char nome1[], char senha1[], char nome2[], float valor){
    usuario *logado = login(u, nome1, senha1);
    usuario *destino = NULL;
    usuario *temp = u; 
    
    if(logado){
        while(temp != NULL){
            if(strcmp(temp->nome, nome2) == 0){
                destino = temp;
                break;
            }
            temp = temp->prox;
        }
        
        if(destino == NULL)
            printf("Usuário destinatário não encontrado ou inexistente.\n");
        else{
            if(valor <= 0){
                printf("Valor de transferência inválido.\n");
                return u;
            }
            
            if(logado->saldo >= valor){
                transacao *novaOrigem = (transacao*)malloc(sizeof(transacao));
                if(novaOrigem){
                    novaOrigem->valor = valor;
                    strcpy(novaOrigem->tipo, "Envio");
                    novaOrigem->prox = logado->extrato;
                    logado->extrato = novaOrigem;
                    

                    transacao *novaDestino = (transacao*)malloc(sizeof(transacao));
                    if(novaDestino){
                        novaDestino->valor = valor;
                        strcpy(novaDestino->tipo, "Recebido");
                        novaDestino->prox = destino->extrato;
                        destino->extrato = novaDestino;
                        logado->saldo -= valor;
                        destino->saldo += valor;
                        
                        printf("Transferência realizada com sucesso!\n");
                    } else {
                        printf("Erro ao registrar transação para o destinatário.\n");
                        free(novaOrigem); 
                    }
                } else {
                    printf("Erro ao realizar transferência.\n");
                }
            } else {
                printf("Saldo insuficiente para realizar a transferência.\n");
            }
        }
    } else {
        printf("Usuário ou senha incorretos.\n");
    }
    
    return u;
}

int main(){
    int op;
    float valor2,deposito1, saque1;
    char senha2[20],nome2[50];
    usuario *u = NULL;
  
    do{ 
        printf("Escolha uma opção.\n");
        printf("1 - Criar usuário\n");
        printf("2 - Login\n");
        printf("0 - Sair\n");
        scanf("%d",&op);
        getchar();
        switch (op)
        {
        case 1:
            printf("Digite seu nome:\n");
            fgets(nome2,50,stdin);
            nome2[strcspn(nome2, "\n")] = 0;
            printf("Digite sua senha:\n");
            fgets(senha2,20,stdin);
            senha2[strcspn(senha2, "\n")] = 0;
            printf("Digite seu saldo inicial:\n");
            scanf("%f",&valor2);
            getchar();
            criarusuario(&u,nome2,senha2,valor2);
            break;
        case 2:
            printf("Digite seu nome:\n");
            fgets(nome2,50,stdin);
            nome2[strcspn(nome2, "\n")] = 0;
            printf("Digite sua senha:\n");
            fgets(senha2,20,stdin);
            senha2[strcspn(senha2, "\n")] = 0;
            if(login(u,nome2,senha2)){
                int op1;
                do
                {
                    printf("Escolha sua opção:\n");
                    printf("1.Deposito.\n");
                    printf("2.Saque.\n");
                    printf("3.Consultar saldo.\n");
                    printf("4.Salvar extrato.\n");
                    printf("5.Ler extrato.\n");
                    printf("6.Transferência.\n");
                    printf("0.Sair.\n");
                    scanf("%d",&op1);
                    getchar();
                    switch (op1)
                    {
                    case 1:
                        printf("Digite o valor a ser depositado: \n");
                        scanf("%f",&deposito1);
                        getchar();
                        if(deposito1 > 0){
                        deposito(u,nome2,senha2,deposito1);}
                        else{
                            printf("Valor inválido.\n");
                        }
                        break;
                    case 2:
                        printf("Digite o valor a ser sacado: \n");
                        scanf("%f",&saque1);
                        getchar();
                        if(saque1 > 0){
                        saque(u,nome2,senha2,saque1);}
                        else{
                            printf("Valor inválido.\n");
                        }
                        break;
                    case 3:
                        consultarsaldo(u,nome2,senha2);
                        break;
                    case 4:
                        salvarExtrato(u);
                        break;
                    case 5:
                        lerExtratoArquivo();
                        break;
                    case 6:
                        printf("Digite o nome do destinatário: \n");
                        fgets(nome2,50,stdin);
                        nome2[strcspn(nome2, "\n")] = 0;
                        printf("Digite o valor a ser transferido: \n");
                        scanf("%f",&valor2);
                        getchar();
                        if(valor2 > 0){
                            u = mandar(u, nome2, senha2, nome2, valor2);
                        } else {
                            printf("Valor inválido.\n");
                        }
                        break;
                    case 0:
                        printf("Saindo do menu de login...\n");
                        break;
                    default:
                        printf("Opção invalida...\n");
                        break;
                    }
                    
                } while (op1 != 0);
            }
            break;
        case 0:
            printf("Saindo...\n");
            break;
        
        default:
            printf("Opção invalida...\n");
            break;
        }
    }while(op != 0);
}