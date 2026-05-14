#include <stdio.h>
#include <string.h>

#define TAM_STRING 50

struct Aluno{
    char nome[TAM_STRING];
    float nota1;
    float nota2;
};

struct Produto{
    char nome[TAM_STRING];
    float preco;
};

struct Indice{
    int indiceMaior;
    int indiceMenor;
};

struct Pessoa{
    char nome[TAM_STRING];
    int idade;
    float altura;
};

void lerStr(char str[], int tamMax);
/*void preencherAluno(struct Aluno a[], int tam);
void calculaMedia(struct Aluno a[], int tam);*/
/*void preencherPessoa(struct Pessoa *p);
void troca(struct Pessoa *a, struct Pessoa *b);
void imprimirPessoa(struct Pessoa p);*/
/*void preencheProduto(struct Produto p[], int tam);
struct Indice produtoMaisCaro(struct Produto p[], int tam);
void exibeProduto(struct Produto p[],struct Indice i);*/
void preenchePessoas(struct Pessoa p[], int tam);
void maisUmAno(struct Pessoa p[], int tam);
void imprimePessoas(struct Pessoa p[], int tam);

int main(){
    struct Aluno alunos[4];
    struct Pessoa pessoas[3];
    struct Produto produtos[3];
    struct Indice produtoMaior;

    /*preencherAluno(alunos, 3);
    calculaMedia(alunos, 3);*/
    /*printf("\n------pessoa A------\n");
    preencherPessoa(&pessoaA);
    printf("\n------pessoa B------\n");
    preencherPessoa(&pessoaB);
    printf("\n------pessoa A------\n");
    imprimirPessoa(pessoaA);
    printf("\n------pessoa B------\n");
    imprimirPessoa(pessoaB);
    printf("\n------troca------\n");
    troca(&pessoaA, &pessoaB);
    printf("\n------pessoa A------\n");
    imprimirPessoa(pessoaA);
    printf("\n------pessoa B------\n");
    imprimirPessoa(pessoaB);*/
    /*preencheProduto(produtos, 3);
    produtoMaior = produtoMaisCaro(produtos, 3);
    exibeProduto(produtos, produtoMaior);*/
    preenchePessoas(pessoas, 3);
    imprimePessoas(pessoas, 3);
    printf("\n-----adiciona um ano------\n");
    maisUmAno(pessoas, 3);
    imprimePessoas(pessoas, 3);
    

    return 0;
}

/*void preencherAluno(struct Aluno a[], int tam){   
    for(int i = 0; i < tam; i++){
        printf("------aluno %d------\n", i + 1);
        printf("Digite o nome do aluno: ");
        lerStr(a[i].nome, TAM_STRING);
        printf("Digite a nota 1: ");
        scanf("%f", &a[i].nota1);
        getchar();
        printf("Digite a nota 2: ");
        scanf("%f", &a[i].nota2);
        getchar();
    }
}

void calculaMedia(struct Aluno a[], int tam){
    float soma = 0, media;

    for(int i = 0; i < tam; i++){
        soma = a[i].nota1 + a[i].nota2;
        media = soma / 2;

        printf("\n------media - aluno %d------\n", i + 1);
        printf("%.2f", media);

        if(media >= 7){
            printf("\naprovado\n");
        }
    }
}*/

/*void preencherPessoa(struct Pessoa *p){
    printf("------preenchimento------\n");
    printf("Digite o nome: ");
    lerStr(p->nome, TAM_STRING);
    printf("Digite sua idade: ");
    scanf("%d", &p->idade);
    getchar();
}

void imprimirPessoa(struct Pessoa p){
    printf("------impressão------\n");
    printf("Nome: %s\n", p.nome);
    printf("Idade: %d\n", p.idade);
}

void troca(struct Pessoa *a, struct Pessoa *b){
    struct Pessoa aux;

    aux = *a;
    *a = *b;
    *b = aux;
}*/

/*void preencheProduto(struct Produto p[], int tam){
    for(int i = 0; i < tam; i++){
        printf("\n------produto %d------\n", i + 1);
        printf("Digite o nome do produto: ");
        lerStr(p[i].nome, TAM_STRING);
        printf("Digite o preço do produto: ");
        scanf("%f", &p[i].preco);
        getchar();
    }
}

struct Indice produtoMaisCaro(struct Produto p[], int tam){
    struct Indice resp;

    resp.indiceMaior = 0;

    for(int i = 0; i < tam; i++){
        if(p[i].preco > p[resp.indiceMaior].preco){
            resp.indiceMaior = i;
        }
    }

    return resp;
}

void exibeProduto(struct Produto p[],struct Indice i){
    printf("\n------produto mais caro------\n");

    printf("Nome: %s\n", p[i.indiceMaior].nome);
    printf("Preço: %f", p[i.indiceMaior].preco);
}*/

void preenchePessoas(struct Pessoa p[], int tam){
    for(int i = 0; i < tam; i++){
        printf("------pessoa %d------\n", i + 1);
        printf("Digite o nome: ");
        lerStr(p[i].nome, TAM_STRING);
        printf("Digite a idade: ");
        scanf("%d", &p[i].idade);
        getchar();
        printf("Digite a altura: ");
        scanf("%f", &p[i].altura);
        getchar();
    }
}

void maisUmAno(struct Pessoa p[], int tam){
    for(int i = 0; i < tam; i++){
        p[i].idade += 1;
    }
}

void imprimePessoas(struct Pessoa p[], int tam){
    for(int i = 0; i < tam; i++){
        printf("\n------impressão - pessoa %d------\n", i + 1);
        printf("Nome %s\n", p[i].nome);
        printf("Idade: %d\n", p[i].idade);
        printf("Altura: %f\n", p[i].altura);
    }
}

void lerStr(char str[], int tamMax){
    fgets(str, tamMax, stdin);

    int tam = strlen(str);

    if(tam > 0 && str[tam - 1] == '\n'){
        str[tam - 1] = '\0';
    }
}