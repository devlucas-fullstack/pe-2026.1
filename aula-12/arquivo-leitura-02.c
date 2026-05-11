#include <stdio.h>

int main(){
    FILE *arq;
    char nomeArq[] = "arquivo.txt";
    int status, num;

    arq = fopen(nomeArq, "rt");

    if(arq == NULL){
        printf("Erro ao abrir arquivo %s\n", nomeArq);
        return 1;
    }

    printf("Arquivo %s aberto com sucesso\n", nomeArq);

    status = fread(&num, sizeof(int), 1, arq);
    while(!feof(arq)){
        if(status == 1){
            printf("Arquivo lido com sucesso: %d\n", num);
        } else {
            printf("Erro ao ler arquivo");
            break;
        }

        status = fread(&num, sizeof(int), 1, arq);
    }

    status = fclose(arq);

    if(status == 0){
        printf("Arquivo %s fechado com sucesso\n", nomeArq);
    } else {
        printf("Erro ao fechar arquivo");
        return 1;
    }

    return 0;
}