#include <stdio.h>
#include <string.h>

#define TAM_FRASE 100

int main(){
    FILE *arq;
    char nomeArq[] = "teste.txt";
    char frase[TAM_FRASE], statusFrase;
    int status;

    arq = fopen(nomeArq, "rt");
    if(arq == NULL){
        printf("Erro ao abrir arquivo\n");
        return 1;
    } else {
        printf("Arquivo %s aberto com sucesso\n", nomeArq);
    }

    printf("------conteúdo do arquivo------\n");
    status = fread(frase, sizeof(char), 10, arq);
    frase[status] = '\0';
    if(status == 10){
        printf("Arquivo %s lido com sucesso\n", nomeArq);
    } else {
        printf("Erro ao ler arquivo\n");
    }

    while(fgets(frase, TAM_FRASE, arq) != NULL){
        printf("%s", frase);
    }

    status = fclose(arq);
    if(status != 0){
        printf("Erro ao fechar arquivo\n");
        return 1;
    } else {
        printf("Arquivo fechado com sucesso\n");
    }


    return 0;
}

void fLerStr(char str[], int tamMax, FILE *arq){
    fgets(str, tamMax, arq);

    int tam = strlen(str);

    if(tam > 0 && str[tam - 1] == '\n'){
        str[tam - 1] = '\0';
    }
}