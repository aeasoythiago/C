// mini_banco_mysql.c - Versão inicial com conexão MySQL

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

#define HOST "localhost"
#define USER "root"
#define PASS "sua_senha"
#define DB   "mini_banco"

MYSQL *conn;

void conectar_mysql() {
    conn = mysql_init(NULL);
    if (conn == NULL) {
        fprintf(stderr, "Erro ao inicializar conexão MySQL\n");
        exit(1);
    }
    if (!mysql_real_connect(conn, HOST, USER, PASS, DB, 0, NULL, 0)) {
        fprintf(stderr, "Erro na conexão: %s\n", mysql_error(conn));
        exit(1);
    }
}

void criar_usuario(char nome[], char senha[], float saldo) {
    char query[300];
    sprintf(query, "INSERT INTO usuarios (nome, senha, saldo) VALUES ('%s', '%s', %.2f)", nome, senha, saldo);
    if (mysql_query(conn, query)) {
        fprintf(stderr, "Erro ao criar usuário: %s\n", mysql_error(conn));
    } else {
        printf("Usuário criado com sucesso!\n");
    }
}

int consultar_saldo(char nome[], char senha[]) {
    char query[300];
    sprintf(query, "SELECT saldo FROM usuarios WHERE nome='%s' AND senha='%s'", nome, senha);
    if (mysql_query(conn, query)) {
        fprintf(stderr, "Erro na consulta: %s\n", mysql_error(conn));
        return 0;
    }

    MYSQL_RES *res = mysql_store_result(conn);
    MYSQL_ROW row = mysql_fetch_row(res);
    if (row) {
        printf("Saldo atual: R$ %s\n", row[0]);
    } else {
        printf("Usuário ou senha incorretos.\n");
    }
    mysql_free_result(res);
    return 1;
}

void mostrar_extrato(char nome[], char senha[]) {
    char query[300];
    sprintf(query, "SELECT id FROM usuarios WHERE nome='%s' AND senha='%s'", nome, senha);
    if (mysql_query(conn, query)) {
        fprintf(stderr, "Erro: %s\n", mysql_error(conn));
        return;
    }
    MYSQL_RES *res = mysql_store_result(conn);
    MYSQL_ROW row = mysql_fetch_row(res);
    if (!row) {
        printf("Usuário ou senha inválidos.\n");
        return;
    }
    int id = atoi(row[0]);
    mysql_free_result(res);

    sprintf(query, "SELECT tipo, valor, data FROM transacoes WHERE usuario_id=%d", id);
    if (mysql_query(conn, query)) {
        fprintf(stderr, "Erro ao buscar transações: %s\n", mysql_error(conn));
        return;
    }
    res = mysql_store_result(conn);
    printf("\n==== Extrato de Transações ===\n");
    while ((row = mysql_fetch_row(res))) {
        printf("%s: R$ %s em %s\n", row[0], row[1], row[2]);
    }
    mysql_free_result(res);
}

int main() {
    conectar_mysql();

    int op;
    char nome[50], senha[20];
    float saldo;

    do {
        printf("\n1 - Criar usuário\n2 - Consultar saldo\n3 - Mostrar extrato\n0 - Sair\n> ");
        scanf("%d", &op);
        getchar();

        switch(op) {
            case 1:
                printf("Nome: "); fgets(nome, sizeof(nome), stdin);
                nome[strcspn(nome, "\n")] = 0;
                printf("Senha: "); fgets(senha, sizeof(senha), stdin);
                senha[strcspn(senha, "\n")] = 0;
                printf("Saldo inicial: R$ "); scanf("%f", &saldo); getchar();
                criar_usuario(nome, senha, saldo);
                break;

            case 2:
                printf("Nome: "); fgets(nome, sizeof(nome), stdin);
                nome[strcspn(nome, "\n")] = 0;
                printf("Senha: "); fgets(senha, sizeof(senha), stdin);
                senha[strcspn(senha, "\n")] = 0;
                consultar_saldo(nome, senha);
                break;

            case 3:
                printf("Nome: "); fgets(nome, sizeof(nome), stdin);
                nome[strcspn(nome, "\n")] = 0;
                printf("Senha: "); fgets(senha, sizeof(senha), stdin);
                senha[strcspn(senha, "\n")] = 0;
                mostrar_extrato(nome, senha);
                break;

            case 0:
                printf("Saindo...\n");
                break;

            default:
                printf("Opção inválida.\n");
        }

    } while(op != 0);

    mysql_close(conn);
    return 0;
}
