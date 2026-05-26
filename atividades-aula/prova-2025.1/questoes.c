#include <stdio.h>
#include <string.h>

#define TAM 100

struct Categoria {
    int codigo;
    char nome[50];
};

struct Produto {
    int codigo;
    char titulo[100];
    char descricao[256];
    int categoria;
    int preco;
};

void lerStr(char str[], int tamMax);
void cadastrarCategoria(struct Categoria v[], int *qtd);
void imprimirCategorias(struct Categoria v[], int qtd);
void imprimirProdutos(struct Produto vp[], int qtdProdutos, struct Categoria vc[], int qtdCategorias);
void selectionSortPorDescricao(struct Produto v[], int qtd);
void buscaBinariaPorDescricao(struct Produto v[], int qtd, char *x);

int main(){
    struct Categoria categorias[TAM];
    struct Produto produtos[TAM];
    int op, qtd = 0;
    char descricao[256], temStr[50];

    do{
        printf("\n=====MENU=====\n");
        printf("1. Cadastrar categoria\n");
        printf("2. Imprimir categorias\n");
        printf("3. Imprimir produtos\n");
        printf("4. Ordenar por descrição\n");
        printf("5. Busca binária por descrição\n");
        printf("0. Sair");
        scanf("%d", &op);
        lerStr(temStr, 50);

        switch(op){
            case 1:
                cadastrarCategoria(categorias, &qtd);
                break;
            case 2:
                imprimirCategorias(categorias, qtd);
                break;
            case 3:
                imprimirProdutos(produtos, qtd, categorias, qtd);
                break;
            case 4:
                selectionSortPorDescricao(produtos, qtd);
                break;
            case 5:
                printf("\nDigite a descrição que deseja buscar: ");
                lerStr(descricao, 256);
                buscaBinariaPorDescricao(produtos, qtd, descricao);
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

void cadastrarCategoria(struct Categoria v[], int *qtd){
    char tempStr[50];
    int codigo;

    if(*qtd >= TAM){
        printf("Não foi possível cadastrar categoria!");
        return;
    }

    printf("\n-----cadastra categoria-----\n");
    printf("Digite o código da categoria: ");
    scanf("%d", &codigo);

    for(int i = 0; i < *qtd; i++){
        if(v[i].codigo == codigo){
            printf("Código já existe!");
            return;
        }
    }

    v[*qtd].codigo = codigo;

    lerStr(tempStr, 50);
    printf("Digite o nome da categoria: ");
    lerStr(v[*qtd].nome, 50);

    *qtd += 1;
}

void imprimirCategorias(struct Categoria v[], int qtd){
    printf("\n-----imprime categoria-----\n");

    for(int i = 0; i < qtd; i++){
        printf("\n-----categoria %d-----\n", i + 1);
        printf("Código: %d\n", v[i].codigo);
        printf("Nome: %s", v[i].nome);
    }
}

void imprimirProdutos(struct Produto vp[], int qtdProdutos, struct Categoria vc[], int qtdCategorias){
    printf("\n-----imprime produtos-----\n");

    for(int i = 0; i < qtdProdutos; i++){
        printf("\n-----produto %d-----\n", i + 1);
        printf("Código: %d\n", vp[i].codigo);
        printf("Nome: %s\n", vp[i].titulo);
        printf("Descrição: %s\n", vp[i].descricao);

        for(int j = 0; j < qtdCategorias; j++){
            if(vc[j].codigo == vp[j].categoria){
                printf("Categoria: %s\n", vc[j].nome);
            }
        }
        printf("Preço: %lf\n", vp[i].preco / 100);
    }
}

void selectionSortPorDescricao(struct Produto v[], int qtd){
    int i, j, menor;
    struct Produto aux;

    for(int i = 0; i < qtd - 1; i++){
        menor = i;

        for(int j = i + 1; j < qtd; j++){
            if(strcmp(v[j].descricao, v[menor].descricao) < 0){
                menor = j;
            }
        }

        aux = v[i];
        v[i] = v[menor];
        v[menor] = aux;
    }
}

void buscaBinariaPorDescricao(struct Produto v[], int qtd, char *x){
    int inicio = 0, fim = qtd - 1;

    while(inicio <= fim){
        int meio = inicio + (fim - inicio) / 2;

        int comparacao = strcmp(v[meio].descricao, x);

        if(comparacao == 0){
            printf("\nProduto encontrado!\n");

            printf("Codigo: %d\n", v[meio].codigo);
            printf("Titulo: %s\n", v[meio].titulo);
            printf("Descricao: %s\n", v[meio].descricao);
            printf("Preco: R$ %.2lf\n", v[meio].preco / 100.0);

            return;
        } else if(comparacao > 0){
            fim = meio - 1;
        } else if(comparacao < 0){
            inicio = meio + 1;
        }
    }
}