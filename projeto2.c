#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct aluno {
    int idade;
    char nome[50];
    float nota;
} aluno;

void salvararquivo(aluno *alunos, int quantidade) {
    FILE *arquivo = fopen("alunos.txt", "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    fprintf(arquivo, "%d\n", quantidade);
    for (int i = 0; i < quantidade; i++) {
        alunos[i].nome[strcspn(alunos[i].nome, "\n")] = '\0';
        fprintf(arquivo, "%s\n", alunos[i].nome);
        fprintf(arquivo, "%d\n", alunos[i].idade);
        fprintf(arquivo, "%.2f\n", alunos[i].nota);
    }

    fclose(arquivo);
}

void lerarquivo(aluno *alunos, int *quantidade) {
    FILE *arquivo = fopen("alunos.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    fscanf(arquivo, "%d\n", quantidade);
    for (int i = 0; i < *quantidade; i++) {
        fgets(alunos[i].nome, sizeof(alunos[i].nome), arquivo);
        alunos[i].nome[strcspn(alunos[i].nome, "\n")] = '\0'; 
        fscanf(arquivo, "%d\n", &alunos[i].idade);
        fscanf(arquivo, "%f\n", &alunos[i].nota);
    }

    fclose(arquivo);
    printf("Arquivo lido com sucesso. %d alunos carregados.\n", *quantidade);
}

int main() {
    aluno alunos[100];
    int quantidade = 0;
    int a, i;
    char nome3[50];

    do {
        printf("\n===== SISTEMA DE CADASTRO DE ALUNOS =====\n");
        printf("1. Adicionar aluno\n");
        printf("2. Listar alunos\n");
        printf("3. Buscar aluno\n");
        printf("4. Mostrar aluno com maior nota\n");
        printf("5. Salvar alunos em arquivo\n");
        printf("6. Ler arquivo salvo\n");
        printf("7. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &a);
        getchar(); // limpar buffer

        switch (a) {
            case 1:
                if (quantidade < 100) {
                    printf("Digite o nome do aluno:\n");
                    fgets(alunos[quantidade].nome, sizeof(alunos[quantidade].nome), stdin);
                    printf("Digite a idade do aluno:\n");
                    scanf("%d", &alunos[quantidade].idade);
                    printf("Digite sua maior nota:\n");
                    scanf("%f", &alunos[quantidade].nota);
                    getchar(); // limpar buffer
                    quantidade++;
                } else {
                    printf("Limite de alunos atingido.\n");
                }
                break;

            case 2:
                for (i = 0; i < quantidade; i++) {
                    printf("\nAluno %d:\n", i + 1);
                    printf("Nome: %s\n", alunos[i].nome);
                    printf("Idade: %d\n", alunos[i].idade);
                    printf("Maior nota: %.2f\n", alunos[i].nota);
                }
                break;

            case 3: {
                int encontrado = 0;
                printf("Digite o nome do aluno:\n");
                scanf(" %[^\n]", nome3); // lê até a quebra de linha
                for (i = 0; i < quantidade; i++) {
                    if (strcmp(alunos[i].nome, nome3) == 0) {
                        printf("Nome completo: %s\n", alunos[i].nome);
                        printf("Idade: %d\n", alunos[i].idade);
                        printf("Maior nota: %.2f\n", alunos[i].nota);
                        encontrado = 1;
                        break;
                    }
                }
                if (!encontrado) {
                    printf("Aluno não cadastrado.\n");
                }
                break;
            }

            case 4:
                if (quantidade == 0) {
                    printf("Nenhum aluno cadastrado.\n");
                } else {
                    float maior = alunos[0].nota;
                    int indice = 0;
                    for (i = 1; i < quantidade; i++) {
                        if (alunos[i].nota > maior) {
                            maior = alunos[i].nota;
                            indice = i;
                        }
                    }
                    printf("Aluno com maior nota:\n%s = %.2f\n", alunos[indice].nome, alunos[indice].nota);
                }
                break;

            case 5:
                salvararquivo(alunos, quantidade);
                printf("Alunos salvos em arquivo.\n");
                break;

            case 6:
                lerarquivo(alunos, &quantidade);
                break;

            case 7:
                printf("Saindo do programa...\n");
                break;

            default:
                printf("Opção inválida.\n");
                break;
        }

    } while (a != 7);

    return 0;
}
