#include <stdio.h>
#include <stdlib.h>

typedef struct aluno{
    int matricula,idade;
    char nome[50];
    float nota;
}aluno;

int main(){
    aluno alunos[100];
    int a,i;
    int quantidade = 0;
    char nome3[50];
    do{
        printf("===== SISTEMA DE CADASTRO DE ALUNOS =====\n");
        printf("1. Adicionar aluno\n");
        printf("2.Listar alunos\n");
        printf("3.Buscar alunos\n");
        printf("4.Mostrar aluno com maior nota\n");
        printf("5.Sair\n");
        printf("Escolha uma opcao:\n");
        scanf("%d",&a);
        getchar();
        switch (a)
        {
        case 1:
            if(quantidade < 100){
            printf("Digite o nome do aluno:\n");
            scanf("%[^\n]",alunos[quantidade].nome);
            printf("Digite a idade do aluno:\n");
            scanf("%d",&alunos[quantidade].idade);
            printf("Digite sua maior nota:\n");
            scanf("%f",&alunos[quantidade].nota);
            getchar();
            quantidade++;
            }
            else{
                printf("Limite de alunos atingido\n");
            }
            break;
        case 2:
            for(i = 0; i < quantidade; i++){
                printf("\nAluno %d:\n", i+1);
                printf("Nome: %s\n", alunos[i].nome);
                printf("Idade: %d\n", alunos[i].idade);
                printf("Maior nota: %.2f\n", alunos[i].nota);
            }
            break;
        case 3:
            int encontrado = 0;
            printf("Digite o nome do aluno:\n");
            scanf("%[^\n]",nome3);
            for(i = 0; i < quantidade; i++){
                if(strcmp(alunos[i].nome,nome3) == 0){
                    printf("Nome completo:%s\n",alunos[i].nome);
                    printf("Idade:%d\n",alunos[i].idade);
                    printf("Maior nota:%f\n",alunos[i].nota);
                    encontrado = 1;
                    break;
                }
            }
            if(!encontrado){
                printf("Aluno nao cadastrado.\n");
            }
            break;
        case 4:
            if(quantidade == 0){
                printf("Nenhum aluno cadastrado.\n");
            }
            else{
                float maior = alunos[0].nota;
                int indice = 0;
                for(i = 1; i < quantidade; i++){
                    if(alunos[i].nota>maior){
                        maior = alunos[i].nota;
                        indice = i;
                    }
                }
                printf("Aluno com maior nota:\n%s = %f",alunos[indice].nome,alunos[indice].nota);
            }
            break;
        case 5:
            printf("Saindo do programa...\n");
            break;
        default:
            printf("Invalido.\n");
            break;
        }
    }while(a!=5);

    return 0;
}
