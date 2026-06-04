#include <stdio.h>
#include <string.h>

#define TAM_STRING 50

struct Livro {
    int id;
    char titulo[TAM_STRING];
    int qtdDisponivel;
    float precoAluguel;
};

struct Emprestimo {
    int id;
    int idCliente;
    int idsLivros[3]; // Limite de 3 livros por empréstimo
    int diasAluguel[3];
};

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

int buscaLivroTitulo(struct Livro v[], int tam, char x[]){
    for(int i = 0; i < tam; i++){
        if(strcmp(v[i].titulo, x) == 0){
            return i;
        }
    }

    return -1;
}

int buscaEmprestimoId(struct Emprestimo v[], int tam, int x){
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

int alteraLivro(struct Livro v[], int tam){
    char titulo[TAM_STRING];
    char opEst, opVlr;
    int pos = 0;

    printf("Digite o título do livro que deseja alterar: ");
    lerStr(titulo, TAM_STRING);

    pos = buscaLivroTitulo(v, tam, titulo);

    if(pos == -1){
        printf("Livro inexistente!");
        return 0;
    }

    printf("Deseja alterar a quantidade disponivel(s/n): ");
    scanf(" %c", &opEst);

    printf("Deseja alterar o preço do aluguel: ");
    scanf(" %c", &opVlr);

    if(opEst == 's'){
        printf("Digite a nova quantidade de estoque: ");
        scanf("%d", &v[pos].qtdDisponivel);
    }

    if(opVlr == 's'){
        printf("Digite o novo valor unitário: ");
        scanf("%f", &v[pos].precoAluguel);
    }

    return 1;
}

void realizaEmprestimo(struct Livro vl[], int tamLivros, struct Emprestimo ve[], int *tamEmprestimos){
    int id, pos = 0, qtdDif, diasAl;
    char titulo[TAM_STRING];

    printf("Digite o ID do empréstimo: ");
    scanf("%d", &id);
    pos = buscaEmprestimoId(ve, *tamEmprestimos, id);

    if(pos != -1){
        printf("Emprétismo já existe!");
        return;
    }

    printf("Digite o ID do cliente: ");
    scanf("%d", &ve[*tamEmprestimos].idCliente);

    do{
        printf("Digite a quantidade de livros diferentes: ");
        scanf("%d", &qtdDif);
    } while(qtdDif < 1 || qtdDif > 3);

    for(int i = 0; i < qtdDif; i++){
        printf("Digite o título do livro %d: ", i + 1);
        lerStr(titulo, TAM_STRING);

        pos = buscaLivroTitulo(vl, tamLivros, titulo);

        if(pos != -1 && vl[pos].qtdDisponivel > 0){
            printf("Digite a quantidade de dias de aluguel do livro %d: ", i + 1);
            scanf("%d", &diasAl);

            vl[pos].qtdDisponivel -= 1;
            ve[*tamEmprestimos].idsLivros[i] = vl[pos].id; 
            ve[*tamEmprestimos].diasAluguel[i] = diasAl;
        }
    }

    ve[*tamEmprestimos].id = id;

    *tamEmprestimos += 1;
}