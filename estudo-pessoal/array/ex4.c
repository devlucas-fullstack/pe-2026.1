#include <stdio.h>

#define TAM_MAX 10

int main(){
    return 0;
}

void carregarConsumo(int v[], int n){
    for(int i = 0; i < n; i++){
        do{
            printf("Digite um número maior que 0(posicao %d): ", i);
            scanf("%d", &v[i]);
        } while(v[i] <= 0);
    }
}

float calcularMediaPontual(int v[], int n){
    float soma = 0;

    for(int i = 0; i < n; i++){
        soma += v[i];
    }

    return soma / (float) n;
}

int buscarAcimaDaMedia(int v[], int n, float media){
    int count = 0;

    for(int i = 0; i < n; i++){
        if(v[i] > media){
            count++;
        }
    }

    return count;
}

void exibirLista(int v[], int n){
    for(int i = 0; i < n; i++){
        printf("Residência [%d]: %d kWh", i, v[i]);
    }
}