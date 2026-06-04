#include <stdio.h>
#include <string.h>

#define MAX_LIVROS 100
#define MAX_USUARIOS 50
#define MAX_EMPRESTIMOS 200
#define TAM_STRING 50

struct Livro{
    int codigo;
    char titulo[TAM_STRING];
    char autor[TAM_STRING];
    int ano;
    int quantidade;
};

struct Usuario{
    int matricula;
    char nome[TAM_STRING];
    char curso[TAM_STRING];
};

struct Emprestimo{
    int codigoLivro;
    int matriculaUsuario;
    char data[11];
    int devolvido; // 0 = não, 1 = sim
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

int buscaCodigoLivro(struct Livro v[], int qtdLivros, int x){
    for(int i = 0; i < qtdLivros; i++){
        if(v[i].codigo == x){
            return i;
        }
    }

    return -1;
}

int buscaMatriculaUsuario(struct Usuario v[], int qtdUsuarios, int x){
    for(int i = 0; i < qtdUsuarios; i++){
        if(v[i].matricula == x){
            return i;
        }
    }

    return -1;
}

int cadastrarLivro(struct Livro vl[], int *qtdLivros){
    int codigo, pos = 0, qtd;
    char tempStr[TAM_STRING];

    printf("Digite o codigo do livro: ");
    scanf("%d", &codigo);
    lerStr(tempStr, TAM_STRING);
    pos = buscaCodigoLivro(vl, *qtdLivros, codigo);

    if(pos != -1){
        printf("Livro já existe!");
        return 0;
    }

    printf("Digite o título do livro: ");
    lerStr(vl[*qtdLivros].titulo, TAM_STRING);

    printf("Digite o autor do livro: ");
    lerStr(vl[*qtdLivros].autor, TAM_STRING);

    printf("Digite o ano do livro: ");
    scanf("%d", &vl[*qtdLivros].ano);
    lerStr(tempStr, TAM_STRING);

    do{
        printf("Digite a quantidade do livro: ");
        scanf("%d", &qtd);
        lerStr(tempStr, TAM_STRING);
    } while(qtd <= 0);

    vl[*qtdLivros].codigo = codigo;
    vl[*qtdLivros].quantidade = qtd;

    *qtdLivros += 1;

    return 1;
}

int cadastrarUsuario(struct Usuario vu[], int *qtdUsuarios){
    int matricula, pos = 0;
    char tempStr[TAM_STRING];

    printf("Digite a matrícula: ");
    scanf("%d", &matricula);
    lerStr(tempStr, TAM_STRING);

    pos = buscaMatriculaUsuario(vu, *qtdUsuarios, matricula);

    if(pos != -1){
        printf("Matrícula já existe!");
        return 0;
    }

    printf("Digite o nome: ");
    lerStr(vu[*qtdUsuarios].nome, TAM_STRING);

    printf("Digite o curso: ");
    lerStr(vu[*qtdUsuarios].curso, TAM_STRING);

    vu[*qtdUsuarios].matricula = matricula;

    *qtdUsuarios += 1;

    return 1;
}

int realizarEmprestimo(struct Livro vl[], int qtdL, struct Usuario vu[], int qtdU, struct Emprestimo ve[], int *qtdE){
    int codigo, matricula, posL = 0, posU = 0;
    char tempStr[TAM_STRING];
    
    printf("Digite o codigo do livro: ");
    scanf("%d", &codigo);
    lerStr(tempStr, TAM_STRING);

    posL = buscaCodigoLivro(vl, qtdL, codigo);

    if(posL == -1){
        printf("Livro não existe!");
        return 0;
    }

    printf("Digite a matrícula do usuário: ");
    scanf("%d", &matricula);
    lerStr(tempStr, TAM_STRING);

    posU = buscaMatriculaUsuario(vu, qtdU, matricula);

    if(posU == -1){
        printf("Usuário não existe!");
        return 0;
    }

    if(vl[posL].quantidade <= 0){
        printf("Livro sem estoque!");
        return 0;
    }

    if(vl[posL].quantidade > 0){
        vl[posL].quantidade -= 1;
        printf("Digite a data(dd/mm/aaaa): ");
        lerStr(ve[*qtdE].data, 11);

        ve[*qtdE].devolvido = 0;
        ve[*qtdE].codigoLivro = codigo;
        ve[*qtdE].matriculaUsuario = matricula;
    }

    *qtdE += 1;

    return 1;
}

int devolverLivro(struct Livro vl[], int qtdLivros, struct Emprestimo ve[], int qtdEmprestimos, int codigoLivro){
    int posL = 0;
    
    posL = buscaCodigoLivro(vl, qtdLivros, codigoLivro);

    if(posL == -1){
        printf("Livro não existe!");
        return 0;
    }

    for(int i = 0; i < qtdEmprestimos; i++){
        if(ve[i].codigoLivro == codigoLivro){
            vl[posL].quantidade += 1;
            ve[i].devolvido = 1;
        }
    }

    return 1;
}

void alterarLivro(struct Livro vl[], int qtdLivros){
    int codigo, pos = 0;
    char tempStr[TAM_STRING];

    printf("Digite o código do livro que você deseja alterar: ");
    scanf("%d", &codigo);
    lerStr(tempStr, TAM_STRING);

    pos = buscaCodigoLivro(vl, qtdLivros, codigo);

    if(pos == -1){
        printf("Livro não existe!");
        return;
    }

    printf("Digite o novo título: ");
    lerStr(vl[pos].titulo, TAM_STRING);

    printf("Digite o novo autor: ");
    lerStr(vl[pos].autor, TAM_STRING);

    printf("Digite o novo ano: ");
    scanf("%d", &vl[pos].ano);
    lerStr(tempStr, TAM_STRING);

    printf("Digite o novo estoque: ");
    scanf("%d", &vl[pos].quantidade);
    lerStr(tempStr, TAM_STRING);
}

int removerLivro(struct Livro vl[], int *qtdLivros, int codigo){
    int pos = 0;

    pos = buscaCodigoLivro(vl, *qtdLivros, codigo);

    if(pos == -1){
        printf("Livro não existe!");
        return 0;
    }

    for(int i = pos; i < *qtdLivros - 1; i++){
        vl[i] = vl[i + 1];
    }

    *qtdLivros -= 1;

    return 1;
}

void ordenarLivros(struct Livro vl[], int qtdLivros){
    int i, fim, pos, troca;
    struct Livro aux;

    troca = 1;
    fim = qtdLivros - 2;
    pos = 0;

    while(troca == 1){
        troca = 0;

        for(i = 0; i <= fim; i++){
            if(strcmp(vl[i].titulo, vl[i + 1].titulo) > 0){
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

int buscaBinariaTitulo(struct Livro vl[], int qtdLivros, char titulo[]){
    int inicio = 0, fim = qtdLivros - 1;

    while(inicio <= fim){
        int meio = inicio + (fim - inicio) / 2;

        if(strcmp(vl[meio].titulo, titulo) == 0){
            return meio;
        } else if(strcmp(vl[meio].titulo, titulo) > 0){
            fim = meio - 1;
        } else {
            inicio = meio + 1;
        }
    }

    return -1;
}

void gerarRelatorio(struct Livro vl[], int qtdL, struct Usuario vu[], int qtdU, struct Emprestimo ve[], int qtdE){
    int empAtivo = 0, maior = 0, maiorUser = 0, maiorQtd = 0;
    
    printf("Total de livros: %d", qtdL);
    printf("Total de usuários: %d", qtdU);
    printf("Total de empréstimos: %d", qtdE);

    for(int i = 0; i < qtdE; i++){
        if(ve[i].devolvido == 0){
            empAtivo += 1;
        }
    }

    printf("Empréstimos ativos: %d", empAtivo);

    for(int i = 0; i < qtdL; i++){
        if(vl[i].quantidade > vl[maior].quantidade){
            maior = i;
        }
    }

    printf("Livro com maior estoque: %s", vl[maior].titulo);

    for(int i = 0; i < qtdU; i++){
        int count = 0;

        for(int j = 0; j < qtdE; j++){
            if(vu[i].matricula == ve[j].matriculaUsuario && ve[j].devolvido == 0){
                count++;
            }
        }

        if(count > maiorQtd){
            maiorQtd = count;
            maiorUser = i;
        }
    }

    printf("Usuário com livros ativos: %s", vu[maiorUser].nome);
}

void listarLivrosUsuario(struct Livro vl[], int qtdL, struct Emprestimo ve[], int qtdE, int matricula){
    for(int i = 0; i < qtdL; i++){
        for(int j = 0; j < qtdE; j++){
            if(ve[j].devolvido == 0 && ve[j].matriculaUsuario == matricula && ve[j].codigoLivro == vl[i].codigo){
                printf("Livro: %s", vl[i].titulo);
            }
        }
    }
}

