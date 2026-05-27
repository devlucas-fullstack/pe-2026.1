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
int buscarVendaPorId(int id, struct Vendas *v);
void cadastrarProduto();
void listarProdutos();
void buscarProduto();
void atualizarProduto();
void removerProduto();
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
        printf("1 - Cadastrar produto\n");
        printf("2 - Listar produtos\n");
        printf("3 - Buscar produto\n");
        printf("4 - Atualizar produto\n");
        printf("5 - Remover produto\n");
        printf("6 - Cadastrar venda\n");
        printf("7 - Listar vendas\n");
        printf("8 - Buscar venda\n");
        printf("9 - Atualizar venda\n");
        printf("10 - Remover venda\n");
        printf("0 - Sair\n");

        printf("\nEscolha uma opção: ");
        scanf("%d", &op);

        switch(op){
            case 1:
                cadastrarProduto();
                break;
            case 2:
                listarProdutos();
                break;
            case 3:
                buscarProduto();
                break;
            case 4:
                atualizarProduto();
                break;
            case 5:
                removerProduto();
                break;
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

int buscarVendaPorId(int id, struct Vendas *v){
    FILE *arq = fopen("vendas.dat", "rb");

    if(arq == NULL){
        return 0;
    }

    while(fread(v, sizeof(struct Vendas), 1, arq)){

        if(v->idVenda == id){
            fclose(arq);
            return 1;
        }
    }

    fclose(arq);
    return 0;
}

void cadastrarProduto(){

    FILE *arq;
    struct Produto p;
    struct Produto temp;
    int idDuplicado;
    char tempStr[TAM_NOME];

    printf("\n---- Cadastro de Produto ----\n");

    // Validação do ID
    do{
        printf("ID: ");
        scanf("%d", &p.id);
        lerStr(tempStr, TAM_NOME);

        if(p.id <= 0){
            printf("ID Invalido. Digite um número  positivo.\n");
            continue;
        }

        arq = fopen("produtos.dat", "rb");
        idDuplicado = 0;

        if(arq != NULL){
            while(fread(&temp, sizeof(struct Produto), 1, arq)){
                if(temp.id == p.id){
                    idDuplicado = 1;
                    break;
                }
            }
            fclose(arq);
        }

        if(idDuplicado){
            printf("ID já cadastrado. Tente outro.\n");
        }
    }while(p.id <= 0 || idDuplicado);

    printf("Nome: ");
    lerStr(p.nome, TAM_NOME);

    do{
        printf("Preço: ");
        scanf("%lf", &p.preco);
        if(p.preco < 0){
            printf("Preço invalido.\n");
        }
    }while(p.preco < 0);

    do {
        printf("Estoque: ");
        scanf("%d", &p.estoque);
        if (p.estoque < 0){
            printf("Estoque invalido.\n");
        }
    } while (p.estoque < 0);

    arq = fopen("produtos.dat", "ab");
    if(arq == NULL){
        printf("\nErro ao abrir arquivo. Produto nao cadastrado.\n");
        return;
    }
    fwrite(&p, sizeof(struct Produto), 1, arq);
    fclose(arq);

    printf("\nProduto cadastrado com sucesso!\n");
}

void listarProdutos(){
    
    FILE *arq;
    struct Produto p;

    arq = fopen("produtos.dat", "rb");

    if(arq == NULL){
        printf("\nNenhum produto cadastrado.\n");
        return;
    }

    printf("\n---- Lista de Produtos ----\n");

    while (fread(&p, sizeof(struct Produto), 1, arq)) {
        printf("\nID: %d\n", p.id);
        printf("Nome: %s\n", p.nome);
        printf("Preco: %.2lf\n", p.preco);
        printf("Estoque: %d\n", p.estoque);
        printf("-----------------------------\n");
    }

    fclose(arq);

}

void buscarProduto(){

    struct Produto p;
    int id;
    char tempStr[TAM_NOME];

    printf("\nDigite o ID do produto: ");
    scanf("%d", &id);
    lerStr(tempStr, TAM_NOME);

    if(buscarProdutoPorId(id, &p)){
        printf("\n---- PRODUTO ENCONTRADO ----\n");
        printf("ID: %d\n", p.id);
        printf("Nome: %s\n", p.nome);
        printf("Preco: %.2lf\n", p.preco);
        printf("Estoque: %d\n", p.estoque);
    } else {
        printf("\nProduto não encontrado.\n");
    }
}

void atualizarProduto(){

    FILE *arq;
    struct Produto p;
    int id;
    int encontrou = 0;
    char tempStr[TAM_NOME];

    printf("\n---- Atualizar Produto ----\n");

    printf("Digite o ID do produto: ");
    scanf("%d", &id);
    lerStr(tempStr, TAM_NOME);

    arq = fopen("produtos.dat", "rb+");

    if(arq == NULL){
        printf("\nNenhum produto cadastrado.\n");
        return;
    }

    while(fread(&p, sizeof(struct Produto), 1, arq)){
        if(p.id == id){
            encontrou = 1;

            printf("\nNovo nome: ");
            lerStr(p.nome, TAM_NOME);

            do {
                printf("Novo preco: ");
                scanf("%lf", &p.preco);
                if (p.preco < 0) printf("Preco invalido.\n");
            } while (p.preco < 0);

            do {
                printf("Novo estoque: ");
                scanf("%d", &p.estoque);
                if (p.estoque < 0) printf("Estoque invalido.\n");
            } while (p.estoque < 0);

            fseek(arq, -(long)sizeof(struct Produto), SEEK_CUR);
            fwrite(&p, sizeof(struct Produto), 1, arq);

            printf("\nProduto atualizado com sucesso!\n");
            break;
        }
    }

    if(!encontrou){
        printf("\nProduto nao encontrado.\n");
    }
    fclose(arq);
}

void removerProduto(){

    FILE *original;
    FILE *temp;
    struct Produto p;
    int id, encontrou = 0;

    printf("\n---- Remover Produto ----\n");

    printf("Digite o ID do produto: ");
    scanf("%d", &id);

    original = fopen("produtos.dat", "rb");

     if (original == NULL) {
        printf("\nNenhum produto cadastrado.\n");
        return;
    }

    temp = fopen("temp.dat", "wb");
    if(temp == NULL){
        printf("\nErro ao criar arquivo temporario.\n");
        fclose(original);
        return;
    }
    
    while (fread(&p, sizeof(struct Produto), 1, original)) {
        if (p.id != id) {
            fwrite(&p, sizeof(struct Produto), 1, temp);
        } else {
            encontrou = 1;
        }
    }

    fclose(original);
    fclose(temp);

    if (encontrou) {
        remove("produtos.dat");
        rename("temp.dat", "produtos.dat");
        printf("\nProduto removido com sucesso!\n");
    } else {
        remove("temp.dat");
        printf("\nProduto nao encontrado.\n");
    }
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

    do{
        printf("ID da venda: ");
        scanf("%d", &v.idVenda);

        if(buscarVendaPorId(v.idVenda, &v)){
            printf("ID ja cadastrado!\n");
        }

    }while(buscarVendaPorId(v.idVenda, &v));

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
            if(p.estoque <= 0){
                printf("Produto sem estoque!\n");
                fclose(arq);
                return;
            }

            v.valorTotal += p.preco;

            FILE *produto = fopen("produtos.dat", "r+b");

            if(produto != NULL){
                struct Produto aux;

                while(fread(&aux, sizeof(struct Produto), 1, produto)){
                    if(aux.id == p.id){
                        aux.estoque--;
                        fseek(produto, -(long)sizeof(struct Produto), SEEK_CUR);
                        fwrite(&aux, sizeof(struct Produto), 1, produto);
                    break;
                    }
                }
            }

            status = fclose(produto);

            if(status != 0){
                printf("\nErro ao fechar arquivo!");
                return;
            }

        } else {
            printf("Produto nao encontrado!\n");
            status = fclose(arq);

            if(status != 0){
                printf("Erro ao fechar arquivo!\n");
                return;
            }

            return;
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
    int encontrou = 0;
    
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
        } else {
            for(int i = 0; i < v.qtdsProduto; i++){
                FILE *produto = fopen("produtos.dat", "rb+");

                if(produto != NULL){
                    struct Produto p;

                    while(fread(&p, sizeof(struct Produto), 1, produto)){
                        if(p.id == v.idsProduto[i]){
                            p.estoque++;
                            fseek(produto, -(long)sizeof(struct Produto), SEEK_CUR);
                            fwrite(&p, sizeof(struct Produto), 1, produto);
                            break;
                        }
                    }

                    status = fclose(produto);

                    if(status != 0){
                        printf("\nErro ao fechar o arquivo!");
                        return;
                    }
                }
            }

            encontrou = 1;
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

    if(encontrou){
        printf("\nVenda removida com sucesso!\n");
    } else {
        printf("\nVenda nao encontrada!\n");
    }
}