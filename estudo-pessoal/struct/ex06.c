#include <string.h>
#include <stdio.h>

#define TAM_NOME 50
#define QTD_PRODUTO 3

struct Produto{
    int id;
    char nome[TAM_NOME];
    int quantidade;
    double preco;
    double valorTotalEstoque;
};

struct Indice{
    int iMaior;
    int iMenor;
};

void lerStr(char str[], int tamMax);
void preencherProduto(struct Produto *p);
void preencherProdutos(struct Produto p[], int qtd);
void bubbleSortPorPreco(struct Produto p[], int qtd);
struct Indice procurarMaisCaro(struct Produto p[], int qtd);
void imprimirPrecos(struct Produto p[], int qtd);

int main(){
    struct Produto produtos[QTD_PRODUTO];
    struct Indice resp;

    preencherProdutos(produtos, QTD_PRODUTO);
    imprimirPrecos(produtos, QTD_PRODUTO);
    bubbleSortPorPreco(produtos, QTD_PRODUTO);
    imprimirPrecos(produtos, QTD_PRODUTO);
    resp = procurarMaisCaro(produtos, QTD_PRODUTO);
    printf("\n-----PRODUTO MAIS CARO-----\n");
    printf("Produto %d: %s", resp.iMaior + 1, produtos[resp.iMaior].nome);

    return 0;
}

void lerStr(char str[], int tamMax){
    fgets(str, tamMax, stdin);

    int tam = strlen(str);

    if(tam > 0 && str[tam - 1] == '\n'){
        str[tam - 1] = '\0';
    }
}

void preencherProduto(struct Produto *p){
    char tempStr[TAM_NOME];

    printf("\n-----PREENCHE PRODUTO-----\n");
    printf("Digite o ID do produto: ");
    scanf("%d", &p->id);
    lerStr(tempStr, TAM_NOME);
    printf("Digite o nome do produto: ");
    lerStr(p->nome, TAM_NOME);
    printf("Digite a quantidade do produto: ");
    scanf("%d", &p->quantidade);
    printf("Digite o preço do produto: ");
    scanf("%lf", &p->preco);
    p->valorTotalEstoque = p->preco * p->quantidade;
}

void preencherProdutos(struct Produto p[], int qtd){
    for(int i = 0; i < qtd; i++){
        printf("\n-----PRODUTO %d-----\n", i + 1);
        preencherProduto(&p[i]);
    }
}

void bubbleSortPorPreco(struct Produto p[], int qtd){
    int i, fim, pos, troca;
    struct Produto aux;

    troca = 1;
    fim = qtd - 2;
    pos = 0;

    while(troca == 1){
        troca = 0;

        for(i = 0; i <= fim; i++){
            if(p[i].preco > p[i + 1].preco){
                aux = p[i];
                p[i] = p[i + 1];
                p[i + 1] = aux;

                troca = 1;
                pos = i;
            }
        }

        fim = pos - 1;
    }
}

struct Indice procurarMaisCaro(struct Produto p[], int qtd){
    struct Indice resp;

    resp.iMaior = 0;

    for(int i = 0; i < qtd; i++){
        if(p[i].preco > p[resp.iMaior].preco){
            resp.iMaior = i;
        }
    }

    return resp;
}

void imprimirPrecos(struct Produto p[], int qtd){
    printf("\n-----IMPRIME PREÇOS-----\n");

    for(int i = 0; i < qtd; i++){
        printf("\n-----PRODUTO %d-----\n", i + 1);
        printf("%.2lf", p[i].preco);
    }
}