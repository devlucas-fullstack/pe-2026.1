#include <stdio.h>
#include <string.h>

#define TAM 100
#define TAM_STRING 50

struct Livro {
    int id;
    char titulo[TAM_STRING];
    char autor[TAM_STRING];
    int qtdEstoque;
    float precoLocacao;
};

struct Locacao {
    int idLocacao;
    int idLivro;
    int qtdDias;
    float valorTotal;
};

int main(){
    return 0;
}

int buscaPorId(struct Livro v[], int qtd, int id){
    for(int i = 0; i < qtd; i++){
        if(v[i].id == id){
            return i;
        }
    }

    return -1;
}

int buscaPorIdLoc(struct Locacao v[], int qtd, int idLoc){
    for(int i = 0; i < qtd; i++){
        if(v[i].idLocacao == idLoc){
            return i;
        }
    }

    return -1;
}

void lerStr(char str[], int tamMax){
    fgets(str, tamMax, stdin);

    int tam = strlen(str);

    if(tam > 0 && str[tam - 1] == '\n'){
        str[tam - 1] = '\0';
    }
}

int cadastrarLivro(struct Livro v[], int *qtd){
    int id, pos = 0;
    char tempStr[TAM_STRING];

    if(*qtd >= TAM){
        printf("Limite de livros atingido!");
        return 0;
    }

    printf("Digite o ID do livro: ");
    scanf("%d", &id);
    lerStr(tempStr, TAM_STRING);

    pos = buscaPorId(v, *qtd, id);

    if(pos != -1){
        printf("Livro já cadastrado!");
        return 0;
    }

    v[*qtd].id = id;

    printf("Digite o titulo do livro: ");
    lerStr(v[*qtd].titulo, TAM_STRING);

    printf("Digite o nome do autor: ");
    lerStr(v[*qtd].autor, TAM_STRING);

    printf("Digite a quantidade em estoque: ");
    scanf("%d", &v[*qtd].qtdEstoque);
    lerStr(tempStr, TAM_STRING);

    printf("Digite o preço da locação: ");
    scanf("%f", &v[*qtd].precoLocacao);
    lerStr(tempStr, TAM_STRING);

    *qtd += 1;

    return 1;
}

void registrarLocacao(struct Livro vl[], int tamLivros, struct Locacao vc[], int *tamLocacoes){
    int idLoc, pos = 0, idLivro;
    float valorTotal = 0;

    printf("Digite o ID da locação: ");
    scanf("%d", &idLoc);

    pos = buscaPorIdLoc(vc, *tamLocacoes, idLoc);

    if(pos != -1){
        printf("Locação já existe!");
        return;
    }

    vc[*tamLocacoes].idLocacao = idLoc;

    printf("Digite o ID do livro desejado: ");
    scanf("%d", &idLivro);

    pos = buscaPorId(vl, tamLivros, idLivro);

    if(pos != -1 && vl[pos].qtdEstoque > 0){
        vc[*tamLocacoes].idLivro = idLivro;

        printf("Quantos dias de locação: ");
        scanf("%d", &vc[*tamLocacoes].qtdDias);

        valorTotal = vl[pos].precoLocacao * vc[*tamLocacoes].qtdDias;
        printf("Valor a ser pago: %.2f", valorTotal);
        vc[*tamLocacoes].valorTotal = valorTotal;

        vl[pos].qtdEstoque -= 1;
        *tamLocacoes += 1;
    } else {
        printf("Livro não foi encontrado ou está esgotado!");
        return;
    }
}

void selectionSortPorTitulo(struct Livro v[], int qtd){
    int i, j, menor;
    struct Livro aux;

    for(i = 0; i < qtd - 1; i++){
        menor = i;

        for(j = i + 1; j <= qtd - 1; j++){
            if(strcmp(v[j].titulo, v[menor].titulo) < 0){
                menor = j;
            }
        }

        aux = v[i];
        v[i] = v[menor];
        v[menor] = aux;
    } 
}

void relatorioEstoqueBaixo(struct Livro v[], int qtd){
    for(int i = 0; i < qtd; i++){
        if(v[i].qtdEstoque < 3){
            printf("ID: %d", v[i].id);
            printf("Título: %s", v[i].titulo);
            printf("Estoque: %d", v[i].qtdEstoque);
        }
    }
}