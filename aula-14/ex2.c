#include <stdio.h>
#include <string.h>

#define TAM_STRING 50
#define QTD_PROD 3

struct Produto{
    int codigo;
    char descricao[TAM_STRING];
    double valor;
    int quantidade;
};

void lerStr(char str[], int tamMax);
void cadastraProduto(struct Produto p[], int *n);
int buscaPorCodigo(struct Produto p[], int qtd, int codigo);
void alteraValor(struct Produto p[], int qtd);
void exibeValor(struct Produto p[], int qtd);
void exibeEstoque(struct Produto p[], int qtd);
void venda(struct Produto p[], int qtd);
void atualizaEstoque(struct Produto p[], int qtd);
void exibeCodigoDescricao(struct Produto p[], int qtd);
void exibeCodigoDescricaoEstoqueZero(struct Produto p[], int qtd);

int main(){
    struct Produto produtos[QTD_PROD];
    int opcao, totalProdutos = 0;

    do{
        printf("\n-----MENU-----\n");

        printf("1. Cadatrar produto\n");
        printf("2. Alterar valor unitário\n");
        printf("3. Exibir valor unitario\n");
        printf("4. Exibir estoque\n");
        printf("5. Processar venda\n");
        printf("6. Atualizar estoque\n");
        printf("7. Exibir código e descrição de todos os produtos\n");
        printf("8. Exibir código e descrição de produto com estoque zero\n");
        printf("Dite 0 p sair\n");
        scanf("%d", &opcao);

        switch(opcao){
            case 1:
                cadastraProduto(produtos, &totalProdutos);
                break;
            case 2:
                alteraValor(produtos, totalProdutos);
                break;
            case 3:
                exibeValor(produtos, totalProdutos);
                break;
            case 4:
                exibeEstoque(produtos, totalProdutos);
                break;
            case 5:
                venda(produtos, totalProdutos);
                break;
            case 6:
                atualizaEstoque(produtos, totalProdutos);
                break;
            case 7:
                exibeCodigoDescricao(produtos, totalProdutos);
                break;
            case 8:
                exibeCodigoDescricaoEstoqueZero(produtos, totalProdutos);
                break;
            case 0:
                printf("Programa encerrado!");

        }
    } while(opcao != 0);

    return 0;
}

void cadastraProduto(struct Produto p[], int *n){
    char tempStr[TAM_STRING];
    printf("-----cadastra produto-----\n");
    printf("Digite o código do produto: ");
    scanf("%d", &p[*n].codigo);
    lerStr(tempStr, TAM_STRING);
    printf("Digite a descrição do produto: ");
    lerStr(p[*n].descricao, TAM_STRING);
    printf("Digite o valor unitário do produto: ");
    scanf("%lf", &p[*n].valor);
    printf("Digite a quantidade em estoque do produto: ");
    scanf("%d", &p[*n].quantidade);
    (*n)++;
}

int buscaPorCodigo(struct Produto p[], int qtd, int codigo){
    for(int i = 0; i < qtd; i++){
        if(p[i].codigo == codigo){
            return i;
        }
    }

    return -1;
}

void alteraValor(struct Produto p[], int qtd){
    double valor;
    int codigo, pos;

    printf("\n-----altera valor-----\n");
    printf("Digite o novo valor do produto: ");
    scanf("%lf", &valor);
    printf("Digite o código do produto que deseja alterar o valor: ");
    scanf("%d", &codigo);

    pos = buscaPorCodigo(p, qtd, codigo);

    if(pos != -1){
        p[pos].valor = valor;
    }

    printf("\nValor alterado com sucesso!\n");
}

void exibeValor(struct Produto p[], int qtd){
    int codigo, pos;

    printf("\n-----exibe valor-----\n");
    printf("Digite o codigo do produto que deseja exibir o valor: ");
    scanf("%d", &codigo);

    pos = buscaPorCodigo(p, qtd, codigo);

    if(pos != -1){
        printf("Produto %d: %.2lf R$", p[pos].codigo, p[pos].valor);
    }
}

void exibeEstoque(struct Produto p[], int qtd){
    int codigo, pos;

    printf("\n-----exibe estoque-----\n");
    printf("Digite o código do produto que deseja exibir o estoque: ");
    scanf("%d", &codigo);

    pos = buscaPorCodigo(p, qtd, codigo);

    if(pos != -1){
        printf("Produto %d: %d", p[pos].codigo, p[pos].quantidade);
    }
}

void venda(struct Produto p[], int qtd){
    int codigo, qtdDesejada, pos;
    double valor = 0;

    printf("\n-----venda-----\n");
    printf("Digite o código do produto: ");
    scanf("%d", &codigo);
    printf("Digite a quantidade desejada: ");
    scanf("%d", &qtdDesejada);

    pos = buscaPorCodigo(p, qtd, codigo);

    if(qtdDesejada <= p[pos].quantidade && pos != -1){
        p[pos].quantidade -= qtdDesejada;
        valor = p[pos].valor * qtdDesejada;
    } else if(p[pos].quantidade == 0){
        printf("Produto com estoque 0");
    }

    printf("Valor a ser pago: %.2lf", valor);
}

void atualizaEstoque(struct Produto p[], int qtd){
    int codigo, estoque, pos;

    printf("\n-----atualiza estoque-----\n");
    printf("Digite o codigo do produto que deseja atualizar o estoque: ");
    scanf("%d", &codigo);
    printf("Digite o novo valor do estoque: ");
    scanf("%d", &estoque);

    pos = buscaPorCodigo(p, qtd, codigo);

    if(pos != -1){
        p[pos].quantidade = estoque;
    }

    printf("Estoque atualizado com sucesso!");
}

void exibeCodigoDescricao(struct Produto p[], int qtd){
    printf("\n-----exibe código e descrição-----\n");

    for(int i = 0; i < qtd; i++){
        printf("-----produto %d-----\n", i + 1);
        printf("Código: %d", p[i].codigo);
        printf("Descrição: %s", p[i].descricao);
    }
}

void exibeCodigoDescricaoEstoqueZero(struct Produto p[], int qtd){
    printf("\n-----exibe codigo e descricao de produtos com estoque zero-----\n");

    for(int i = 0; i < qtd; i++){
        if(p[i].quantidade == 0){
            exibeCodigoDescricao(p, qtd);
        }
    }
}

void lerStr(char str[], int tamMax){
    fgets(str, tamMax, stdin);

    int tam = strlen(str);

    if(tam > 0 && str[tam - 1] == '\n'){
        str[tam - 1] = '\0';
    }
}