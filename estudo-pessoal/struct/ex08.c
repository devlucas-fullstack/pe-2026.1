#include <stdio.h>
#include <string.h>

#define TAM_AUTOR 50
#define TAM_LIVRO 200
#define TAM_STRING 50

struct Autor {
    int codigo;
    char nome[TAM_STRING];
};

struct Livro {
    int codigo;
    char titulo[TAM_STRING];
    int codAutor;
    int qtdEstoque;
    float precoBase;
};

void lerStr(char str[], int tamMax);
void cadastrarLivro(struct Livro vl[], int *qtdLivros, struct Autor va[], int qtdAutores);

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

void cadastrarLivro(struct Livro vl[], int *qtdLivros, struct Autor va[], int qtdAutores){
    int codigo, achou = 0, codAutor, autorExiste = 0;
    char tempStr[TAM_STRING];

    printf("\n-----CADASTRA LIVROS-----\n");

    if(*qtdLivros >= TAM_LIVRO){
        printf("Limite de livros atingidos!\n");
        return;
    }

    do{
        achou = 0;
        printf("Digite o código do livro: ");
        scanf("%d", &codigo);

        for(int i = 0; i < *qtdLivros; i++){
            if(vl[i].codigo == codigo){
                printf("Código já existe!");
                achou = 1;
                break;
            }
        }
    } while(achou == 1);

    vl[*qtdLivros].codigo = codigo;

    printf("Digite o código do autor: ");
    scanf("%d", &codAutor);
    lerStr(tempStr, TAM_STRING);

    for(int i = 0; i < qtdAutores; i++){
        if(va[i].codigo == codAutor){
            autorExiste = 1;
            break;
        }
    }

    if(autorExiste == 1){
        vl[*qtdLivros].codAutor = codAutor;
    } else {
        printf("Autor não existe!");
        return;
    }
    
    printf("Digite o título: ");
    lerStr(vl[*qtdLivros].titulo, TAM_STRING);

    printf("Digite o estoque: ");
    scanf("%d", &vl[*qtdLivros].qtdEstoque);

    printf("Digite o preço: ");
    scanf("%f", &vl[*qtdLivros].precoBase);

    *qtdLivros += 1;
}

void bubbleSort(struct Livro vl[], int qtdLivros){
    int i, fim, pos, troca;
    struct Livro aux;

    troca = 1;
    fim = qtdLivros - 2;
    pos = 0;

    while(troca == 1){
        troca = 0;

        for(i = 0; i <= fim; i++){
            if(vl[i].codigo > vl[i + 1].codigo){
                aux = vl[i];
                vl[i] = vl[i + 1];
                vl[i + 1] = aux;

                troca = 1;
                pos = i;
            }
        }

        fim = pos - 1;
    }
}

int buscaBinariaCodigoLivro(struct Livro vl[], int qtdLivros, int cod){
    int inicio = 0, fim = qtdLivros - 1;

    while(inicio <= fim){
        int meio = inicio + (fim - inicio) / 2;

        if(vl[meio].codigo == cod){
            return meio;
        } else if(vl[meio].codigo > cod){
            fim = meio - 1;
        } else if(vl[meio].codigo < cod){
            inicio = meio + 1;
        }
    }

    return -1;
}

void imprimirRelatorio(struct Livro vl[], int qL, struct Autor va[], int qA){
    printf("\n-----IMPRIMIR RELATORIO-----\n");

    int pos, cod, posAutor;
    float precoMulta = 0;

    printf("Digite o código do livro: ");
    scanf("%d", &cod);

    pos = buscaBinariaCodigoLivro(vl, qL, cod);

    printf("Título: %s\n", vl[pos].titulo);
    
    for(int i = 0; i < qA; i++){
        if(vl[pos].codAutor == va[i].codigo){
            posAutor = i;
        }
    }

    printf("Nome do autor: %s\n", va[posAutor].nome);
    
    precoMulta = (vl[pos].precoBase * 2) / 100;

    printf("Valor da multa: R$ %.2f", precoMulta);
}

void imprimirRelatorios(struct Livro vl[], int qL, struct Autor va[], int qA){
    int pos, posAutor;
    float precoMulta = 0;

    printf("\n-----IMPRIME RELATÓRIOS-----\n");

    for(int i = 0; i < qL; i++){
        printf("Título: %s\n", vl[i].titulo);
        
        for(int j = 0; j < qA; j++){
            if(va[j].codigo == vl[j].codAutor){
                posAutor = j;
            }
        }

        printf("Nome do autor: %s\n", va[posAutor].nome);
        
        precoMulta = (vl[i].precoBase * 2) / 100;

        printf("Valor da multa: R$ %.2f", precoMulta);
    }
}

void ordenarLivrosPorTitulo(struct Livro v[], int qtd){
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

void realizarEmprestimo(struct Livro vl[], int qL){
    int codigo, pos;
    char op;

    printf("\n-----EMPRESTIMO DE LIVROS-----\n");

    printf("Digite o código do livro: ");
    scanf("%d", &codigo);

    pos = buscaBinariaCodigoLivro(vl, qL, codigo);

    if(pos == -1){
        printf("Livro não existe!");
        return;
    }

    if(vl[pos].qtdEstoque > 0){
        printf("tem certeza que deseja fazer o empréstimo(s/n): ");
        scanf("%c", &op);

        if(op == 's'){
            vl[pos].qtdEstoque -= 1;
        }
    } else {
        printf("Livro sem estoque!");
    }
}