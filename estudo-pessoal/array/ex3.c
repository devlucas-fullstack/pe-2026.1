#include <stdio.h>

#define TAM_MAX 10

int main(){
    return 0;
}

void preencherLeituras(int v[], int n){
    int valor;

    for(int i = 0; i < n; i++){
        do{
            printf("Digite valores inteiros: ");
            scanf("%d", &valor);

            if(valor <= 0){
                printf("Erro ao preencher leitura!");
            }
        } while(valor <= 0);

        v[i] = valor;
    }
}

void ordenarDecrescente(int v[], int n){
    int i, fim, pos, troca;
    int aux;

    troca = 1;
    fim = n - 1;
    pos = 0;

    while(troca == 1){
        troca = 0;

        for(i = 0; i <= fim; i++){
            if(v[i] < v[i + 1]){
                aux = v[i];
                v[i] = v[i + 1];
                v[i + 1] = aux;

                troca = 1;
                pos = i;
            }
        }

        fim = pos - 1;
    }
}

int encontrarFrequencia(int v[], int n, int x){
    int count = 0;

    for(int i = 0; i < n; i++){
        if(v[i] == x){
            count += 1;
        }
    }

    return count;
}

void separarFaixas(int v[], int n, int limite, int menores[], int maiores[]){
    int posMenores = 0, posMaiores = 0;
    
    for(int i = 0; i < n; i++){
        if(v[i] < limite){
            menores[posMenores] = v[i];
            posMenores++;
        }
    }

    for(int i = 0; i < n; i++){
        if(v[i] >= limite){
            maiores[posMaiores] = v[i];
            posMaiores++;
        }
    }

    for(int i = posMenores; i < TAM_MAX; i++){
        menores[i] = -1;
    }

    for(int i = posMaiores; i < TAM_MAX; i++){
        maiores[i] = -1;
    }
}

void imprimirFormatado(int v[], int n){
    int count = 0;

    for(int i = 0; i < n; i++){
        if(v[i] != -1){
            printf(" %d -", v[i]);
        }

        if(v[i] == -1){
            count++;
        }
    }

    if(count == n){
        printf("Vetor vazio");
    }
}