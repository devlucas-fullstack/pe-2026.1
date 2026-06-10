#include <stdio.h>

#define TAM_MAX 10

int main(){
    return 0;
}

void preencherTransacoes(int v[], int n){
    for(int i = 0; i < n; i++){
        do{
            printf("Digite valores inteiros: ");
            scanf("%d", &v[i]);

            if(v[i] < 0){
                printf("Valor inválido!");
            }
        } while(v[i] < 0);
    }
}

int filtrarTransacoes(int v[], int n, int limite){
    int tamAtual = n;

    for(int i = 0; i < tamAtual; i++){
        if(v[i] > limite){
            for(int j = i; j < tamAtual - 1; j++){
                v[j] = v[j + 1];
            }

            v[tamAtual - 1] = -1;
            tamAtual--;
        }
    }

    return tamAtual;
}