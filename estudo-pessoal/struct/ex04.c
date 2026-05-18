#include <stdio.h>
#include <string.h>

#define QTD_CAD 3
#define TAM_STRING 30

struct Cadastro{
    int codigo;
    char descricao[TAM_STRING];
    float valor;
    int quantidade;
};

void lerStr(char str[], int tamMAX);
void cadastraProduto(struct Cadastro *p);
void cadastraProdutos(struct Cadastro p[], int tam);
int buscaCodigo(struct Cadastro p[], int tam, int cod);
void alteraValor(struct Cadastro p[], int tam);
void imprimirValor(struct Cadastro p[], int tam);
void atualizaEstoque(struct Cadastro p[], int tam);
void imprimirEstoque(struct Cadastro p[], int tam);
void imprimeCodigoDescricao(struct Cadastro p[], int tam);
void processaVenda(struct Cadastro p[], int tam);
void venda(struct Cadastro p[], int pos, int qtd);
void imprimeCodigoDescricaoEstoqueZero(struct Cadastro p[], int tam);

int main(){
    struct Cadastro cadastros[QTD_CAD];

    cadastraProdutos(cadastros, QTD_CAD);
    alteraValor(cadastros, QTD_CAD);
    imprimirValor(cadastros, QTD_CAD);
    atualizaEstoque(cadastros, QTD_CAD);
    processaVenda(cadastros, QTD_CAD);
    imprimirEstoque(cadastros, QTD_CAD);
    imprimeCodigoDescricao(cadastros, QTD_CAD);
    imprimeCodigoDescricaoEstoqueZero(cadastros, QTD_CAD);

    return 0;
}

void cadastraProduto(struct Cadastro *p){
    printf("Digite o código do produto: ");
    scanf("%d", &p->codigo);
    getchar();
    printf("Digite a descrição do produto: ");
    lerStr(p->descricao, TAM_STRING);
    printf("Digite o valor do produto: ");
    scanf("%f", &p->valor);
    getchar();
    printf("Digite a quantidade do produto: ");
    scanf("%d", &p->quantidade);
    getchar();
}

void cadastraProdutos(struct Cadastro p[], int tam){
    printf("------cadastro de produtos-----\n");

    for(int i = 0; i < tam; i++){
        printf("-----produto %d-----\n", i + 1);
        cadastraProduto(&p[i]);
    }
}

int buscaCodigo(struct Cadastro p[], int tam, int cod){
    for(int i = 0; i < tam; i++){
        if(p[i].codigo == cod){
            return i;
        }
    }

    return -1;
}

void alteraValor(struct Cadastro p[], int tam){
    char opcao;
    int cod, pos;
    float valor;

    do{
        printf("\n-----altera valor do produto-----\n");

        printf("Digite o código do produto que você deseja alterar: ");
        scanf("%d", &cod);
        getchar();
        pos = buscaCodigo(p, tam, cod);
        
        printf("Digite o novo valor do produto: ");
        scanf("%f", &valor);
        getchar();

        p[pos].valor = valor;

        printf("Você deseja altera o valor de algum produto(s/n): ");
        scanf("%c", &opcao);
        getchar();
    } while(opcao != 'n');
}

void imprimirValor(struct Cadastro p[], int tam){
    char opcao;
    int cod, pos;

    do{
        printf("\n-----imprime valor do produto-----\n");

        printf("Digite o código do produto que deseja imprimir: ");
        scanf("%d", &cod);
        getchar();

        pos = buscaCodigo(p, tam, cod);

        printf("Valor do produto %d: %.2f\n", pos + 1, p[pos].valor);

        printf("Você deseja imprimir o valor de algum produto(s/n)? ");
        scanf("%c", &opcao);
        getchar();
    } while(opcao == 's');
}

void imprimirEstoque(struct Cadastro p[], int tam){
    char opcao;
    int cod, pos;

    do{
        printf("\n-----imprime estoque do produto-----\n");

        printf("Digite o código do produto que deseja impimir o estoque: ");
        scanf("%d", &cod);
        getchar();

        pos = buscaCodigo(p, tam, cod);

        printf("Estoque do produto %d: %d\n", pos + 1, p[pos].quantidade);

        printf("Você deseja imprimir o estoque de mais algum produto(s/n)? ");
        scanf("%c", &opcao);
        getchar();
    } while(opcao == 's');
}

void atualizaEstoque(struct Cadastro p[], int tam){
    char opcao;
    int cod, pos, valor;

    do{
        printf("\n-----atualiza estoque do produto-----\n");

        printf("Digite o código do produto que deseja atualizar o estoque: ");
        scanf("%d", &cod);
        getchar();

        pos = buscaCodigo(p, tam, cod);

        printf("Digite o novo estoque do produto: ");
        scanf("%d", &valor);
        getchar();

        p[pos].quantidade = valor;

        printf("Você deseja atualizar o estoque de mais algum produto(s/n)? ");
        scanf("%c", &opcao);
        getchar();
    } while(opcao == 's');
}

void imprimeCodigoDescricao(struct Cadastro p[], int tam){
    printf("\n-----imprime código e descrição-----\n");

    for(int i = 0; i < tam; i++){
        printf("-----produto %d-----\n", i + 1);

        printf("Código: %d\n", p[i].codigo);
        printf("Descrição: %s\n", p[i].descricao);
    }
}

void imprimeCodigoDescricaoEstoqueZero(struct Cadastro p[], int tam){
    printf("\n-----imprime código e descrição de produtos sem estoque-----\n");

    for(int i = 0; i < tam; i++){
        if(p[i].quantidade == 0){
            printf("-----produto %d-----\n", i + 1);

            printf("Código: %d\n", p[i].codigo);
            printf("Descrição: %s\n", p[i].descricao);
        }
    }
}

void processaVenda(struct Cadastro p[], int tam){
    char opcao, opcaoCompra;
    int cod, qtd, pos;

    do{
        printf("\n-----vendas-----\n");

        printf("Digite o código do produto para ser vendido: ");
        scanf("%d", &cod);
        getchar();

        pos = buscaCodigo(p, tam, cod);

        if(p[pos].quantidade == 0){
            printf("Produto sem estoque!");
            return;
        }

        printf("Digite a quantidade de produtos que deseja comprar: ");
        scanf("%d", &qtd);
        getchar();

        if(qtd < p[pos].quantidade){
            printf("Deseja efetivar a compra(s/n)?");
            scanf("%c", &opcaoCompra);
        }

        if(opcaoCompra == 's'){
            venda(p, pos, qtd);
            printf("Valor a ser pago: %f\n", p[pos].valor * qtd);
        }

        printf("Deseja processar mais alguma venda(s/n)? ");
        scanf("%c", &opcao);
        getchar();
    } while(opcao == 's');
}

void venda(struct Cadastro p[], int pos, int qtd){
    p[pos].quantidade = p[pos].quantidade - qtd;
}

void lerStr(char str[], int tamMAX){
    fgets(str, tamMAX, stdin);

    int tam = strlen(str);

    if(tam > 0 && str[tam - 1] == '\n'){
        str[tam - 1] = '\0';
    }
}