#include <stdio.h>

#define QTD 5

int main(){
    FILE *arq;
    char nomeArq[] = "arquivo.txt";
    int status, num;

    arq = fopen(nomeArq, "wt");

    if(arq == NULL){
        printf("Erro ao abrir o arquivo %s\n", nomeArq);
        return 1;
    } 

    printf("Arquivo %s aberto com sucesso\n", nomeArq);

    for(int i = 0; i < QTD; i++){
        printf("Digite um número inteiro: ");
        scanf("%d", &num);

        status = fwrite(&num, sizeof(int), 1, arq);
        if(status == 1){
            printf("Registro gravado com sucesso\n");
        } else {
            printf("Erro ao gravar registro!");
            break;
        }
    }

    status = fclose(arq);
    if(status == 0){
        printf("Arquivo %s fechado com sucesso", nomeArq);
    } else {
        printf("Erro ao fechar arquivo");
        return 1;
    }

    return 0;
}