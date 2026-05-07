#include <stdio.h>

int main(){
    FILE *arq;
    char nomeArq[30] = "teste.txt";
    int status, num = 10;

    // abre
    arq = fopen(nomeArq, "wt");

    if(arq == NULL){
        printf("Erro ao tentar criar o arquivo %s\n", nomeArq);
        return 2;
    } else {
        printf("Arquivo %s criado com sucesso\n", nomeArq);
    }

    // grava
    status = fwrite(&num, sizeof(int), 1, arq);

    if(status != 1){
        printf("Erro ao gravar no arquivo\n");
        return 2;
    } else {
        printf("Dado gravado no arquivo com sucesso\n");
    }

    // fecha
    status = fclose(arq);

    if(status == 0){
        printf("Arquivo fechado com sucesso");
    } else {
        printf("Erro ao tentar fechar o arquivo");
        return 2;
    }

    return 0;
}

