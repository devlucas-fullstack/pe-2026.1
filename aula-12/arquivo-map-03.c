#include <stdio.h>

int main(){
    FILE *arq;
    char nomeArq[] = "arquivo.txt";
    int status, num;

    arq = fopen(nomeArq, "r+t");

    if(arq == NULL){
        printf("Erro ao abrir arquivo %s\n", nomeArq);
        return 1;
    }

    printf("Arquivo %s aberto com sucesso\n", nomeArq);

    status = fread(&num, sizeof(int), 1, arq);

    while(!feof(arq)){
        if(status == 1){
            printf("Arquivo lido com sucesso: %d\n", num);
            num = num * 2;
            status = fseek(arq, -sizeof(int), SEEK_CUR);
            if(status == 0){
                status = fwrite(&num, sizeof(int), 1, arq);

                if(status == 1){
                    printf("Arquivo atualizado com sucesso\n");
                    fflush(arq);
                } else {
                    printf("Erro na atualização do arquivo\n");
                    break;
                }
            } else {
                printf("Erro no posicionamento do ponteiro\n");
                break;
            }
        } else {
            printf("Erro na leitura do arquivo\n");
            break;
        }

        status = fread(&num, sizeof(int), 1, arq);
    }

    status = fclose(arq);
    if(status == 0){
        printf("Arquivo fechado com sucesso\n");
    } else {
        printf("Erro ao fechar arquivo\n");
        return 1;
    }

    return 0;
}