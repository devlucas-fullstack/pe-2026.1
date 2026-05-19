#include <stdio.h>
#include <string.h>

#define TAM_NOME 50
#define QTD_ESTADOS 26

struct Estado {
    char nome[TAM_NOME];
    int numVeiculos;
    int numAcidente;
};

struct Extremos {
    int indiceMaior;
    int indiceMenor;
};

void lerStr(char str[], int tamMAX);
void preencher(struct Estado *e, int tam);
struct Extremos maiorMenorAcidentes(struct Estado e[], int tam);
void maiorNumeroAcidentes(struct Estado e[], struct Extremos *indice);
void menorNumeroAcidente(struct Estado e[], struct Extremos *indice);
void percentualAcidentes(struct Estado e[], int tam);
float mediaAcidentesPais(struct Estado e[], int tam);
void acimaMedia(struct Estado e[], float media, int tam);

int main(){
    struct Estado estados[QTD_ESTADOS];
    struct Extremos resultado;
    float media;

    preencher(estados, QTD_ESTADOS);
    resultado = maiorMenorAcidentes(estados, QTD_ESTADOS);
    maiorNumeroAcidentes(estados, &resultado);
    menorNumeroAcidente(estados, &resultado);
    percentualAcidentes(estados, QTD_ESTADOS);
    media = mediaAcidentesPais(estados, QTD_ESTADOS);
    printf("\n-----media de acidentes do pais-----\n");
    printf("%f", media);
    acimaMedia(estados, media, QTD_ESTADOS);

    return 0;
}

void preencher(struct Estado *e, int tam){
    for(int i = 0; i < tam; i++){
        printf("-----estado %d-----\n", i + 1);
        printf("Digite o nome do estado: ");
        lerStr(e[i].nome, TAM_NOME);
        printf("Digite o número de veículos do estado: ");
        scanf("%d", &e[i].numVeiculos);
        printf("Digite o número de acidentes do estado: ");
        scanf("%d", &e[i].numAcidente);
        getchar();
    }
}

struct Extremos maiorMenorAcidentes(struct Estado e[], int tam){
    struct Extremos resp;

    resp.indiceMaior = 0;
    resp.indiceMenor = 0;

    for(int i = 0; i < tam; i++){
        if(e[i].numAcidente > e[resp.indiceMaior].numAcidente){
            resp.indiceMaior = i;
        } else if(e[i].numAcidente < e[resp.indiceMenor].numAcidente){
            resp.indiceMenor = i;
        }
    }

    return resp;
}

void maiorNumeroAcidentes(struct Estado e[], struct Extremos *indice){
    printf("\n-----nome de estado com mais acidentes-----\n");

    printf("%s\n", e[indice->indiceMaior].nome);
    printf("%d", e[indice->indiceMaior].numAcidente);
}

void menorNumeroAcidente(struct Estado e[], struct Extremos *indice){
    printf("\n-----nome de estado com menos acidente-----\n");

    printf("%s\n", e[indice->indiceMenor].nome);
    printf("%d", e[indice->indiceMenor].numAcidente);
}

void percentualAcidentes(struct Estado e[], int tam){
    float percentual = 0.0;

    for(int i = 0; i < tam; i++){
        percentual = ((float)e[i].numAcidente / e[i].numVeiculos) * 100;

        printf("\n-----estado %d-----\n", i + 1);
        printf("%f\n", percentual);
    }
}

float mediaAcidentesPais(struct Estado e[], int tam){
    int soma = 0;

    for(int i = 0; i < tam; i++){
        soma += e[i].numAcidente;
    }

    return (float) soma / tam;
}

void acimaMedia(struct Estado e[], float media, int tam){
    printf("\n-----estados com numero de acidentes acima da media-----\n");

    for(int i = 0; i < tam; i++){
        if(e[i].numAcidente > media){
            printf("%s\n", e[i].nome);
        }
    }
}

void lerStr(char str[], int tamMAX){
    fgets(str, tamMAX, stdin);

    int tam = strlen(str);

    if(tam > 0 && str[tam - 1] == '\n'){
        str[tam - 1] = '\0';
    }
}