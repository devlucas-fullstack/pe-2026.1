#include <stdio.h>
#include <string.h>

#define TAM_NOME 50
#define MAX_PRODUTO 10

struct Produto {
    int id;
    char nome[TAM_NOME];
    double preco;
    int estoque;
};

struct Vendas {
    int idVenda;
    char cliente[TAM_NOME];
    int qtdsProduto;
    int idsProduto[MAX_PRODUTO];
    double valorTotal;
};

void lerStr(char str[], int tamMax);
int buscarProdutoPorId(int id, struct Produto * p);
void cadastrarVenda();
void listarVendas();
void buscarVenda();
void atualizarVenda();
void removerVenda(); 

int main(){
    int op;

    do{
        printf("\n------------------------------\n");
        printf("SISTEMA DE VENDAS E ESTOQUE\n");
        printf("------------------------------\n");
        printf("6 - Cadastrar venda\n");
        printf("7 - Listar vendas\n");
        printf("8 - Buscar venda\n");
        printf("9 - Atualizar venda\n");
        printf("10 - Remover venda\n");
        printf("0 - Sair\n");

        printf("\nEscolha uma opção: ");
        scanf("%d", &op);

        switch(op){
            case 6:
                cadastrarVenda();
                break;
            case 7:
                listarVendas();
                break;
            case 8:
                buscarVenda();
                break;
            case 9:
                atualizarVenda();
                break;
            case 10:
                removerVenda();
                break;
            case 0:
                printf("\nEncerrando...\n");
                break;
            default:
                printf("\nOpcao invalida.\n");
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

int buscarProdutoPorId(int id, struct Produto * p){
    FILE *arq = fopen("produtos.dat", "rb");

    if(arq == NULL){
        return 0;
    }

    while (fread(p, sizeof(struct Produto), 1, arq)) {
        if (p->id == id) {
            fclose(arq);
            return 1;
        }
    }

    fclose(arq);
    return 0;
}

void cadastrarVenda(){
    FILE *arq;
    int status;
    char tempStr[TAM_NOME];

    arq = fopen("vendas.dat", "ab");

    if(arq == NULL){
        printf("Erro ao abrir o arquivo!");
        return;
    }

    struct Produto p;
    struct Vendas v;

    printf("\n-----Cadastro de Venda-----\n");

    printf("ID da venda: ");
    scanf("%d", &v.idVenda);
    lerStr(tempStr, TAM_NOME);
    printf("Nome do cliente: ");
    lerStr(v.cliente, TAM_NOME);
    printf("Quantidade de produtos: ");
    scanf("%d", &v.qtdsProduto);

    if(v.qtdsProduto > MAX_PRODUTO){
        printf("Limite maximo excedido!\n");
        fclose(arq);
        return;
    }

    v.valorTotal = 0;

    for(int i = 0; i < v.qtdsProduto; i++){
        printf("ID do produto %d: ", i + 1);
        scanf("%d", &v.idsProduto[i]);

        if(buscarProdutoPorId(v.idsProduto[i], &p)) {
            v.valorTotal += p.preco;
        }
    }
    
    status = fwrite(&v, sizeof(v), 1, arq);

    if(status == 1){
        printf("\nVenda cadastrada com sucesso!\n");
    }

    status = fclose(arq);

    if(status != 0){
        printf("Erro ao fechar o arquivo!");
    }
}

void listarVendas(){
    FILE *arq;
    int status;

    arq = fopen("vendas.dat", "rb");

    if(arq == NULL){
        printf("Erro ao abrir arquivo!");
        return;
    }

    struct Vendas v;
    struct Produto p;

    printf("\n-----Lista Vendas-----\n");

    while(fread(&v, sizeof(v), 1, arq) == 1){
        printf("\nID da venda: %d\n", v.idVenda);
        printf("Nome do cliente: %s\n", v.cliente);
        printf("Produtos: \n");

        for(int i = 0; i < v.qtdsProduto; i++) {

            if(buscarProdutoPorId(v.idsProduto[i], &p)) {
                printf("- %s (ID %d)\n", p.nome, p.id);
            } else {
                printf("- Produto ID %d nao encontrado\n", v.idsProduto[i]);
            }
        }

        printf("Valor total: %.2f\n", v.valorTotal);
    }

    status = fclose(arq);

    if(status != 0){
        printf("\nErro ao fechar o arquivo!\n");
    }
}

void buscarVenda(){
    FILE *arq;
    int status;
    int id;
    int encontrou = 0;

    arq = fopen("vendas.dat", "rb");

    if(arq == NULL){
        printf("Erro ao abrir arquivo!");
        return;
    }

    struct Vendas v;

    printf("\nDigite o ID da venda: ");
    scanf("%d", &id);

    while(fread(&v, sizeof(v), 1, arq) == 1){
        if(v.idVenda == id){
            encontrou = 1;

            printf("\n-----Venda Encontrada-----\n");
            printf("ID: %d\n", v.idVenda);
            printf("Cliente: %s\n", v.cliente);
            printf("Quantidade de produtos: %d\n", v.qtdsProduto);
            printf("Valor total: %.2lf\n", v.valorTotal);

            break;
        }
    }

    if(!encontrou){
        printf("\nVenda não encontrada!\n");
    }

    status = fclose(arq);

    if(status != 0){
        printf("Erro ao fechar o arquivo!");
    }
}

void atualizarVenda(){
    FILE *arq;
    int status;
    int id;
    int encontrou = 0;
    char tempStr[TAM_NOME];

    arq = fopen("vendas.dat", "r+b");

    if(arq == NULL){
        printf("Erro ao abrir arquivo!");
        return;
    }

    struct Vendas v;

    printf("\nDigite o ID da venda que deseja atualizar: ");
    scanf("%d", &id);

    while(fread(&v, sizeof(v), 1, arq) == 1){
        if(v.idVenda == id){
            encontrou = 1;

            printf("Novo nome do cliente: ");
            lerStr(tempStr, TAM_NOME);
            lerStr(v.cliente, TAM_NOME);

            fseek(arq, -sizeof(v), SEEK_CUR);
            fwrite(&v, sizeof(v), 1, arq);

            printf("\nVenda atualizada com sucesso!\n");

            break;
        }
    }

    if(!encontrou){
        printf("Venda não encontrada!");
    }

    status = fclose(arq);

    if(status != 0){
        printf("\nErro ao fechar o arquivo!\n");
    }
}

void removerVenda(){
    FILE *arq;
    FILE *novo; 
    int id, status;
    
    arq = fopen("vendas.dat", "rb");

    if(arq == NULL){
        printf("Erro ao abrir arquivo: vendas.dat");
        return;
    }

    novo = fopen("temp.dat", "wb");

    if(novo == NULL){
        fclose(arq);
        printf("Erro ao abrir arquivo: temp.dat");
        return;
    }

    struct Vendas v;

    printf("\nDigite o ID da venda que deseja remover: ");
    scanf("%d", &id);

    while(fread(&v, sizeof(v), 1, arq) == 1) {

        if(v.idVenda != id) {
            fwrite(&v, sizeof(v), 1, novo);
        }
    }

    status = fclose(arq);

    if(status != 0){
        printf("\nErro ao fechar arquivo vendas.dat!\n");
    }

    status = fclose(novo);

    if(status != 0){
        printf("\nErro ao fechar arquivo temp.dat!\n");
    }

    remove("vendas.dat");
    rename("temp.dat", "vendas.dat");

    printf("\nVenda removida com sucesso!\n");
}