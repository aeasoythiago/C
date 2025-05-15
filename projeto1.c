#include <stdio.h>
#include <stdlib.h>

int somar(int a, int b){
    return a + b;
}

int diminuir(int a, int b){
    return a - b;
}

int multi(int a, int b){
    return a * b;
}

float dividir(float a, float b){
    return a / b;
}

int main(){
    int a, b, c;
    float d, e;
    do{
        printf("===== CALCULADORA =====\n1.Soma\n2.Subtracao\n3.Multiplicacao\n4.Divisao\n5.Sair\nEscolha uma opcao:");
        scanf("%d",&a);
        switch(a)
        {
        case 1:
            printf("Digite dois numeros para serem somados:\n");
            scanf("%d %d",&b,&c);
            printf("resultado:%d\n",somar(b,c));  
            break;
        case 2:
            printf("Digite dois numeros para serem subtraidos:\n");
            scanf("%d %d",&b,&c);
            printf("resultado:%d\n",diminuir(b,c));
            break;
        case 3:
            printf("Digite dois numeros pare serem multiplicados:\n");
            scanf("%d %d",&b,&c);
            printf("resultado:%d\n",multi(b,c));
            break;
        case 4:
            printf("Digites dois numeros para serem divididos:\n");
            scanf("%f %f",&d,&e);
            printf("resultado:%.2f\n",dividir(d,e));
            break;
        case 5:
            printf("Saindo...\n");
            break;
        }
    }while(a!=5);
}
