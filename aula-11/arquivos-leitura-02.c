#include <stdio.h>

int main(){
    FILE *arq;
    char nomeArq[30] = "teste.txt";
    int status, num;

    arq = fopen(nomeArq, "rt");

    if(arq == NULL){
        printf("Erro ao abrir arquivo %s\n", nomeArq);
        return 2;
    } else {
        printf("Arquivo %s aberto com sucesso\n", nomeArq);
    }

    status = fread(&num, sizeof(int), 1, arq);

    if(status != 1){
        printf("Erro ao ler arquivo\n");
        return 2;
    } else {
        printf("Arquivo lido com sucesso: %d\n", num);
    }

    return 0;
}