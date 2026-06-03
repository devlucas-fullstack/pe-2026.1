#include <stdio.h>
#include <string.h>

#define TAM_STRING 50
#define MAX_PROD 50
#define MAX_CAT 10

struct Categoria {
    int idCat;
    char nomeCat[TAM_STRING];
};

struct Produto {
    int idProd;
    char descricao[TAM_STRING];
    int idCategoria;
    float preco;
    int estoque;
};

void lerStr(char str[], int tamMax);
void cadastrarProduto(struct Produto vp[], int *qtdP, struct Categoria vc[], int qtdC);

int main(){
    return 0;
}

void lerStr(char str[], int tamMax){
    fgets(str, tamMax, stdin);

    int tam = strlen(str);

    if(tam > 0 && str[tam - 1] == '\n'){
        str[tam - 1] = '\0';
    }
}

void cadastrarProduto(struct Produto vp[], int *qtdP, struct Categoria vc[], int qtdC){
    int id, idCategoria, achouIdCat = 0;
    char tempStr[TAM_STRING];

    printf("-----CADASTRA PRODUTO-----\n");

    if(*qtdP >= MAX_PROD){
        printf("Limite de produtos atingido!");
        return;
    }

    printf("Digite o ID do produto: ");
    scanf("%d", &id);
    lerStr(tempStr, TAM_STRING);

    for(int i = 0; i < *qtdP; i++){
        if(vp[i].idProd == id){
            printf("ID já cadastrado!");
            return;
        }
    }

    vp[*qtdP].idProd = id;

    printf("Digite o ID da categoria: ");
    scanf("%d", &idCategoria);
    lerStr(tempStr, TAM_STRING);

    for(int i = 0; i < qtdC; i++){
        if(vc[i].idCat == idCategoria){
            achouIdCat = 1;
            break;
        }
    }

    if(achouIdCat == 1){
        vp[*qtdP].idCategoria = idCategoria;
    } else {
        printf("Esse id de categoria não existe!");
        return;
    }

    printf("Digite a descrição do produto: ");
    lerStr(vp[*qtdP].descricao, TAM_STRING);

    printf("Digite o preço do produto: ");
    scanf("%f", &vp[*qtdP].preco);
    lerStr(tempStr, TAM_STRING);

    printf("Digite o estoque do produto: ");
    scanf("%d", &vp[*qtdP].estoque);
    lerStr(tempStr, TAM_STRING);

    *qtdP += 1;

    printf("Produto cadastrado com sucesso!");
}

int localizarPorDescricao(struct Produto v[], int qtd, char descProcurada[]){
    for(int i = 0; i < qtd; i++){
        if(strcmp(v[i].descricao, descProcurada) == 0){
            return i;
        }
    }

    return -1;
}

void ordenarPorPreco(struct Produto v[], int qtd){
    int i, j, pos, troca, fim;
    struct Produto aux;

    troca = 1;
    fim = qtd - 2;
    pos = 0;

    while(troca == 1){
        troca = 0;

        for(i = 0; i <= fim; i++){
            if(v[i].preco > v[i + 1].preco){
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

void gerarRelatorioGeral(struct Produto vp[], int qP, struct Categoria vc[], int qC){
    int jCategoria;

    for(int i = 0; i < qP; i++){
        printf("Produto %d", i + 1);

        printf("Descrição: %s", vp[i].descricao);
        printf("Preço: %.2f", vp[i].preco);
        
        for(int j = 0; j < qC; j++){
            if(vp[i].idCategoria == vc[j].idCat){
                jCategoria = j;
            }
        }

        printf("Categoria: %s", vc[jCategoria].nomeCat);

        if(vp[i].estoque == 0){
            printf("Produto esgotado!");
        } else {
            printf("Estoque: %d", vp[i].estoque);
        }
    }
}

void processarVenda(struct Produto vp[], int qP){
    int idProduto, acheiId = 0, qtd, produto;
    float valor = 0;
    char op;
    char tempStr[TAM_STRING];

    printf("Digite o ID do produto: ");
    scanf("%d", &idProduto);
    lerStr(tempStr, TAM_STRING);

    for(int i = 0; i < qP; i++){
        if(vp[i].idProd == idProduto){
            acheiId = 1;
            produto = i;
            break;
        }
    }

    if(acheiId == 1){
        printf("Digite a quantidade desejada: ");
        scanf("%d", &qtd);
        lerStr(tempStr, TAM_STRING);

        if(qtd <= vp[produto].estoque){
            vp[produto].estoque -= qtd;
            valor = vp[produto].preco * qtd;
            printf("Valor a pagar: %.2f", valor);
        } else if(qtd > vp[produto].estoque){
            printf("Quantidade insuficiente. Deseja levar as %d unidades restantes(s/n)?", vp[produto].estoque);
            scanf("%c", &op);

            if(op == 's'){
                valor = vp[produto].preco * vp[produto].estoque;
                printf("Valor a pagar: %.2f", valor);
                vp[produto].estoque = 0;
            }
        }
    }
}