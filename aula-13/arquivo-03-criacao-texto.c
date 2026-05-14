#include <stdio.h>
#include <string.h>

#define TAM_FRASE 100

void lerStr(char str[], int tamMax);

int main(){
    FILE *arq;
    char nomeArq[] = "teste.txt";
    char frase[TAM_FRASE];
    int status, tamFrase;

    arq = fopen(nomeArq, "wt");
    if(arq == NULL){
        printf("Erro ao tentar abrir o arquivo!\n");
        return 1;
    } else {
        printf("Arquivo %s aberto com sucesso\n", nomeArq);
    }

    printf("Digite frases(linha em branco para finalizar): \n");
    lerStr(frase, TAM_FRASE);
    tamFrase = strlen(frase);
    status = fprintf(arq, "%s\n", frase);
    while(tamFrase > 0 && status == tamFrase + 1){
        printf("Digite frases(linha em branco para finalizar): \n");
        lerStr(frase, TAM_FRASE);
        tamFrase = strlen(frase);
        status = fprintf(arq, "%s\n", frase);
    }

    status = fclose(arq);
    if(status != 0){
        printf("Erro ao fechar o arquivo");
        return 1;
    } else {
        printf("Arquivo fechado com sucesso");
    }

    return 0;
}

void lerStr(char str[], int tamMax){
    fgets(str, tamMax, stdin);

    int tam = strlen(str);

    if(tam > 0 && str[tam - 1] == '\n'){
        str[tam - 1] = '\0';
    }
}