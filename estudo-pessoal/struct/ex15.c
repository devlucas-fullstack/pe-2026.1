#include <stdio.h>
#include <string.h>

#define TAM_STRING 50

struct Produto {
    int id;
    char descricao[TAM_STRING];
    int qtdEstoque;
    float vlrUnit;
};

struct Venda {
    int id;
    int qtdProdutosVendidos;
    int idsProdutos[5];
    int qtdsVendidas[5];
};

void lerStr(char str[], int tamMax){
    fgets(str, tamMax, stdin);

    int tam = strlen(str);

    if(tam > 0 && str[tam - 1] == '\n'){
        str[tam - 1] = '\0';
    }
}

int buscaSequencialDesc(struct Produto v[], int tam, char x[]){
    for(int i = 0; i < tam; i++){
        if(strcmp(v[i].descricao, x) == 0){
            return i;
        }
    }

    return -1;
}

int buscaBinariaId(struct Venda v[], int tam, int x){
    int inicio = 0, fim = tam - 1;

    while(inicio <= fim){
        int meio = inicio + (fim - inicio) / 2;

        if(v[meio].id == x){
            return meio;
        } else if(v[meio].id > x){
            fim = meio - 1;
        } else {
            inicio = meio + 1;
        }
    }

    return -1;
}

int alteraProduto(struct Produto v[], int tam){
    char desc[TAM_STRING];
    int pos = 0;
    char opDesc, opEst, opVlr;
    char tempStr[TAM_STRING];

    printf("Digite a descrição do produto que deseja alterar: ");
    lerStr(desc, TAM_STRING);

    pos = buscaSequencialDesc(v, tam, desc);

    if(pos == -1){
        printf("Produto não esta cadastrado!");
        return 0;
    }

    printf("Deseja alterar a descrição(s/n): ");
    scanf(" %c", &opDesc);
    lerStr(tempStr, TAM_STRING);

    printf("Deseja alterar o estoque(s/n): ");
    scanf(" %c", &opEst);
    lerStr(tempStr, TAM_STRING);

    printf("Deseja alterar o valor unitário(s/n): ");
    scanf(" %c", &opVlr);
    lerStr(tempStr, TAM_STRING);

    if(opDesc == 's'){
        printf("Digite a nova descrição do produto: ");
        lerStr(v[pos].descricao, TAM_STRING);
    }

    if(opEst == 's'){
        printf("Digite o novo valor de estoque: ");
        scanf("%d", &v[pos].qtdEstoque);
        lerStr(tempStr, TAM_STRING);
    }

    if(opVlr == 's'){
        printf("Digite o novo valor unitário: ");
        scanf("%f", &v[pos].vlrUnit);
        lerStr(tempStr, TAM_STRING);
    }

    return 1;
}

void venda(struct Produto vp[], int tamProd, struct Venda vv[], int *tamVendas){
    int idVenda, qtdDif, qtdProd;
    int pos = 0;
    char desc[TAM_STRING];
    char tempStr[TAM_STRING];

    printf("Digite o ID da venda: ");
    scanf("%d", &idVenda);
    lerStr(tempStr, TAM_STRING);
    pos = buscaBinariaId(vv, *tamVendas, idVenda);

    if(pos != -1){
        printf("Venda já existe!");
        return;
    }

    vv[*tamVendas].id = idVenda;

    do{
        printf("Digite a quantidade de produtos diferentes: ");
        scanf("%d", &qtdDif);
        lerStr(tempStr, TAM_STRING);
    } while(qtdDif < 1 || qtdDif > 5);

    for(int i = 0; i < qtdDif; i++){
        printf("Digite a descrição do produto %d: ", i + 1);
        lerStr(desc, TAM_STRING);
        pos = buscaSequencialDesc(vp, tamProd, desc);

        if(pos != -1 && vp[pos].qtdEstoque > 0){
            do{
                printf("Digite a quantidade de produtos do produto %d: ", i + 1);
                scanf("%d", &qtdProd);
                lerStr(tempStr, TAM_STRING);
            } while(qtdProd < 1 || qtdProd > vp[pos].qtdEstoque);
   
            vv[*tamVendas].idsProdutos[i] = vp[pos].id;
            vv[*tamVendas].qtdsVendidas[i] = qtdProd;
            vp[pos].qtdEstoque -= qtdProd;     
        }
    }

    vv[*tamVendas].qtdProdutosVendidos = qtdDif;

    *tamVendas += 1;
}

void relatorio(struct Produto vp[], int tamProd, struct Venda vv[], int tamVendas){
    int pos = 0;

    for(int i = 0; i < tamVendas; i++){
        if(vv[i].qtdProdutosVendidos > 2){
            printf("Venda %d", i + 1);
            
            for(int j = 0; j < vv[i].qtdProdutosVendidos; j++){
                printf("Quantidade do produto %d: %d", i + 1, vv[i].qtdsVendidas[j]);
                printf("Descrição do produto %d: %s", vp[i].descricao);
                printf("Valor unitário: %.2f", vp[i].vlrUnit);
                printf("Valor total: %.2f", vv[i].qtdsVendidas[j] * vp[i].vlrUnit);
            }

        }
    }
}
