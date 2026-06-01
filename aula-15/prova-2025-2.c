#include <stdio.h>
#include <string.h>

#define TAM_NOME 20

struct Produto{
    int id;
    char descricao[TAM_NOME];
    int estoque;
    float vlrUnitario;
};

struct Venda{
    int id;
    int qtdProdutosVendidos;
    int idsProdutos[5];
    int qtdsVendidas[5];
};

int main(){
    return 0;
}

int buscaSequencialDesc(struct Produto v[], int tam, char x[]){
    for(int i = 0; i < tam; i++){
        if(strcmp(v[i].descricao, x) == 0){
            return i;
        }
    }

    return -1;
}

int buscaBinariaId(struct Venda v[], int tam, int x){
    int inicio = 0, fim = tam - 1;

    while(inicio <= fim){
        int meio = inicio + (fim - inicio) / 2;

        if(v[meio].id == x){
            return meio;
        } else if(v[meio].id > x){
            fim = meio - 1;
        } else if(v[meio].id < x){
            inicio = meio + 1;
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

int alteraProduto(struct Produto v[], int tam){
    char descricaoAltera[TAM_NOME];
    char op;
    int alterou = 0;

    printf("Digite a descrição do produto que você deseja alterar: ");
    lerStr(descricaoAltera, TAM_NOME);

    for(int i = 0; i < tam; i++){
        if(strcmp(v[i].descricao, descricaoAltera) == 0){
            printf("Deseja alterar a descrição(s/n): ");
            scanf("%c", &op);

            if(op == 's'){
                printf("Digite a nova descrição: ");
                lerStr(v[i].descricao, TAM_NOME);
                alterou += 1;
            }

            printf("Deseja alterar o estoque(s/n): ");
            scanf("%c", &op);

            if(op == 's'){
                printf("Digite o novo estoque: ");
                scanf("%d", &v[i].estoque);
                alterou += 1;
            }

            printf("Deseja alterar o valor unitário(s/n): ");
            scanf("%c", &op);

            if(op == 's'){
                printf("Digite o novo valor unitário: ");
                scanf("%f", &v[i].vlrUnitario);
                alterou += 1;
            }
        }

        break;
    }

    if(alterou > 0){
        return 1;
    } else {
        return 0;
    }
}

void venda(struct Produto vp[], int tamProd, struct Venda vv[], int tamVendas){
    int idVenda, qtdDiff, iProduto, qtdVenda;
    char descBusca[TAM_NOME];

    printf("Digite o ID da venda: ");
    scanf("%d", &idVenda);

    for(int i = 0; i < tamVendas; i++){
        if(vv[i].id == idVenda){
            printf("ID de venda já existe!");
            return;
        }
    }

    vv[tamVendas].id = idVenda;
    vv[tamVendas].qtdProdutosVendidos = 0;

    do{
        printf("Digite a quantidade de produtos diferentes que deseja comprar: ");
        scanf("%d", &qtdDiff);
    } while(qtdDiff >= 1 && qtdDiff <= 5);

    for(int i = 0; i < qtdDiff; i++){
        printf("Digite a descrição do produto %d: i + 1");
        lerStr(descBusca, TAM_NOME);

        for(int j = 0; j < tamProd; j++){
            if(strcmp(vp[j].descricao, descBusca) == 0){
                iProduto = j;
            }
        }

        printf("Digite a quantidade do produto %d que deseja comprar: ", i + 1);
        scanf("%d", &qtdVenda);

        if(qtdVenda >= 1 && qtdVenda <= vp[iProduto].estoque){
            vp[iProduto].estoque -= qtdVenda;
            int posAtual = vv[tamVendas].qtdProdutosVendidos;
            vv[tamVendas].idsProdutos[posAtual] = vp[iProduto].id;
            vv[tamVendas].qtdsVendidas[posAtual] = qtdVenda;
            vv[tamVendas].qtdProdutosVendidos++; 
        }
    }
}

