#include <stdio.h>
#include <string.h>

#define TAM_NOME 50
#define QTD_LIVROS 3

struct Livro{
    char titulo[TAM_NOME];
    char autor[TAM_NOME];
    int isbn;
    int paginas;
};

struct NumPagina{
    int maior;
    int menor;
};

void lerStr(char str[], int tamMax);
void preencherLivro(struct Livro *l, int *total);
struct NumPagina maiorNumeroPaginas(struct Livro l[], int qtd);
void exibirMaiorNumeroPaginas(struct Livro l[], int qtd);
struct NumPagina menorNumeroPagina(struct Livro l[], int qtd);
void exibirMenorNumeroPaginas(struct Livro l[], int qtd);
void buscarPorAutor(struct Livro l[], int qtd);
int atualizarPaginas(struct Livro l[], int qtd);

int main(){
    struct Livro livros[QTD_LIVROS];
    int op, totalProdutos = 0;
    char tempStr[TAM_NOME];

    do{
        printf("=====MENU=====\n");
        printf("1. Cadastrar livro\n");
        printf("2. Exibir maior número de páginas\n");
        printf("3. Exibir menor número de páginas\n");
        printf("4. Buscar livro por autor\n");
        printf("5. Atualizar o número de páginas\n");
        printf("0. Sair\n");
        printf("Opção: ");
        scanf("%d", &op);
        lerStr(tempStr, TAM_NOME);

        switch(op){
            case 1: 
                preencherLivro(&livros[totalProdutos], &totalProdutos); 
                break;
            case 2:
                exibirMaiorNumeroPaginas(livros, totalProdutos);
                break;
            case 3:
                exibirMenorNumeroPaginas(livros, totalProdutos);
                break;
            case 4:
                buscarPorAutor(livros, totalProdutos);
                break;
            case 5:
                atualizarPaginas(livros, totalProdutos);
                break;
            case 6:
                printf("\nEncerrando...");
                break;
        }        
    } while(op != 0);

    return 0;
}

void lerStr(char str[], int tamMax){
    fgets(str, tamMax, stdin);

    int tam = strlen(str);

    if(tam > 0 && str[tam - 1] == '\n'){
        str[tam - 1] = '\0';
    }
}

void preencherLivro(struct Livro *l, int *total){
    char tempStr[TAM_NOME];

    printf("\n-----PREENCHE LIVRO-----\n");

    printf("Digite o título do livro: ");
    lerStr(l->titulo, TAM_NOME);
    printf("Digite o autor do livro: ");
    lerStr(l->autor, TAM_NOME);
    printf("Digite o isbn do livro: ");
    scanf("%d", &l->isbn);
    printf("Digite a quantidade de páginas do livro: ");
    scanf("%d", &l->paginas);
    lerStr(tempStr, TAM_NOME);

    *total += 1;
}

struct NumPagina maiorNumeroPaginas(struct Livro l[], int qtd){
    struct NumPagina resp;

    resp.maior = 0;

    for(int i = 0; i < qtd; i++){
        if(l[i].paginas > l[resp.maior].paginas){
            resp.maior = i;
        }
    }

    return resp;
}

void exibirMaiorNumeroPaginas(struct Livro l[], int qtd){
    struct NumPagina resp;

    resp = maiorNumeroPaginas(l, qtd);

    printf("\n-----LIVRO COM MAIS PÁGINAS-----\n");
    printf("Livro %d\n", resp.maior + 1);
    printf("Título: %s\n", l[resp.maior].titulo);
    printf("Autor: %s\n", l[resp.maior].autor);
    printf("ISBN: %d\n", l[resp.maior].isbn);
    printf("Número de páginas: %d\n", l[resp.maior].paginas);
}

struct NumPagina menorNumeroPagina(struct Livro l[], int qtd){
    struct NumPagina resp;

    resp.menor = 0;

    for(int i = 0; i < qtd; i++){
        if(l[i].paginas < l[resp.menor].paginas){
            resp.menor = i;
        }
    }

    return resp;
}

void exibirMenorNumeroPaginas(struct Livro l[], int qtd){
    struct NumPagina resp;

    resp = menorNumeroPagina(l, qtd);

    printf("\n-----LIVRO COM MENOS PÁGINAS-----\n");
    printf("Livro %d\n", resp.menor + 1);
    printf("Título: %s\n", l[resp.menor].titulo);
    printf("Autor: %s\n", l[resp.menor].autor);
    printf("ISBN: %d\n", l[resp.menor].isbn);
    printf("Quantidade de páginas: %d\n", l[resp.menor].paginas);
}

void buscarPorAutor(struct Livro l[], int qtd){
    char nomeAutor[TAM_NOME];
    int encontrou = 0;

    printf("\n-----BUSCAR LIVRO POR AUTOR-----\n");

    printf("Digite o nome do auto: ");
    lerStr(nomeAutor, TAM_NOME);

    for(int i = 0; i < qtd; i++){
        if(strcmp(l[i].autor, nomeAutor) == 0){
            printf("Livro %d\n", i + 1);
            printf("Título: %s\n", l[i].titulo);
            printf("ISBN: %d", l[i].isbn);
            encontrou = 1;
        };
    }

    if(encontrou == 0){
        printf("\nLivro não encontrado!\n");
    }
}

int atualizarPaginas(struct Livro l[], int qtd){
    int isbn, numPag, encontrou = 0;

    printf("\n-----ATUALIZAR PÁGINA-----\n");

    printf("Digite o ISBN do livro que deseja atualizar: ");
    scanf("%d", &isbn);

    printf("Digite o novo número de páginas do livro: ");
    scanf("%d", &numPag);

    for(int i = 0; i < qtd; i++){
        if(l[i].isbn == isbn){
            l[i].paginas = numPag;
            encontrou = 1;
        }
    }

    if(encontrou == 1){
        printf("\nAtualizado com sucesso!\n");
    } else {
        printf("\nLivro não foi enontrado!\n");
    }
}