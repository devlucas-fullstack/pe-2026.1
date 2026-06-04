#include <stdio.h>
#include <string.h>

#define TAM_STRING 50
#define MAX_CONTAS 4

struct Cadastro{
    int numConta;
    char nome[TAM_STRING];
    char cpf[15];
    char telefone[20];
    double saldo;
};

void lerStr(char str[], int tamMax);
int buscaContaNum(struct Cadastro vc[], int qtdCadastro, int numConta);
void cadastraConta(struct Cadastro vc[], int *qtdCadastro, int numConta);
void consultarSaldo(struct Cadastro vc[], int qtdCadastro, int numConta);
void deposito(struct Cadastro vc[], int qtdCadastro, int numConta);
void saque(struct Cadastro vc[], int qtdCadastro, int numConta);
void exibirContas(struct Cadastro vc[], int qtdCadastro);

int main(){
    struct Cadastro contaCorrente[MAX_CONTAS];
    struct Cadastro contaPoupanca[MAX_CONTAS];

    int qtdCadastroC = 0;
    int qtdCadastroP = 0;
    int op, tipoCad, numConta;
    int pos = 0;

    do{
        printf("\n=====MENU=====\n");
        printf("1. Buscar conta\n");
        printf("2. Cadastrar conta\n");
        printf("3. Consultar conta\n");
        printf("4. Depósito\n");
        printf("5. Saque\n");
        printf("6. Exibir contas\n");
        printf("0. Sair\n");
        printf("Opção: ");
        scanf("%d", &op);

        if(op >= 1 && op <= 6){
            printf("\nEm qual cadastro? (1 - Corrente | 2 - Poupanca): ");
            scanf("%d", &tipoCad);

            if(op != 6){
            printf("\nDigite o número da conta: ");
            scanf("%d", &numConta);
        }
        }

        switch(op){
            case 1:
                printf("\n-----BUSCA CONTA-----\n");
                if(tipoCad == 1){
                    pos = buscaContaNum(contaCorrente, qtdCadastroC, numConta);
                    printf("\nPosição da conta: %d", pos + 1);
                } else {
                    pos = buscaContaNum(contaPoupanca, qtdCadastroC, numConta);
                    printf("\nPosição da conta: %d", pos + 1);
                }
                break;
            case 2:
                printf("\n-----CADASTRA CONTA-----\n");
                if(tipoCad == 1){
                    cadastraConta(contaCorrente, &qtdCadastroC, numConta);
                } else {
                    cadastraConta(contaPoupanca, &qtdCadastroP, numConta);
                }
            break;
            case 3:
                printf("\n-----CONSULTA SALDO-----\n");
                if(tipoCad == 1){
                    consultarSaldo(contaCorrente, qtdCadastroC, numConta);
                } else {
                    consultarSaldo(contaPoupanca, qtdCadastroP, numConta);
                }
                break;
            case 4:
                printf("\n-----DEPÓSITO-----\n");
                if(tipoCad == 1){
                    deposito(contaCorrente, qtdCadastroC, numConta);
                } else {
                    deposito(contaPoupanca, qtdCadastroP, numConta);
                }
                break;
            case 5:
                printf("\n-----SAQUE-----\n");
                if(tipoCad == 1){
                    saque(contaCorrente, qtdCadastroC, numConta);
                } else {
                    saque(contaPoupanca, qtdCadastroP, numConta);
                }
                break;
            case 6:
                printf("\n-----EXIBE CONTAS-----\n");
                if(tipoCad == 1){
                    exibirContas(contaCorrente, qtdCadastroC);
                } else {
                    exibirContas(contaPoupanca, qtdCadastroP);
                }
                break;
            case 7:
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

int buscaContaNum(struct Cadastro vc[], int qtdCadastro, int numConta){
    if(qtdCadastro == 0){
        printf("Cadastro vazio!\n");
        return -1;
    }

    for(int i = 0; i < qtdCadastro; i++){
        if(vc[i].numConta == numConta){
            return i;
        }
    }

    return -2;
}

void cadastraConta(struct Cadastro vc[], int *qtdCadastro, int numConta){
    int pos = buscaContaNum(vc, *qtdCadastro, numConta);
    char tempStr[TAM_STRING];

    if(pos >= 0){
        printf("Conta já cadastrada!\n");
        return;
    }

    vc[*qtdCadastro].numConta = numConta;

    lerStr(tempStr, TAM_STRING);

    printf("Digite o nome: ");
    lerStr(vc[*qtdCadastro].nome, TAM_STRING);

    printf("Digite o cpf(000.000.000-00): ");
    lerStr(vc[*qtdCadastro].cpf, TAM_STRING);

    printf("Digite o número do telefone: ");
    lerStr(vc[*qtdCadastro].telefone, TAM_STRING);

    printf("Digite o saldo: ");
    scanf("%lf", &vc[*qtdCadastro].saldo);
    lerStr(tempStr, TAM_STRING);

    *qtdCadastro += 1;

    printf("Conta cadastrada com sucesso!");
}

void consultarSaldo(struct Cadastro vc[], int qtdCadastro, int numConta){
    int pos = buscaContaNum(vc, qtdCadastro, numConta);

    if(pos >= 0){
        printf("Saldo: %.2lf", vc[pos].saldo);
    } else{
        printf("Conta não está cadastrada!");
        return;
    }
}

void deposito(struct Cadastro vc[], int qtdCadastro, int numConta){
    int pos = buscaContaNum(vc, qtdCadastro, numConta);
    double vlrDep;

    if(pos >= 0){
        printf("Digite o valor do depósito: ");
        scanf("%lf", &vlrDep);

        vc[pos].saldo += vlrDep;
    } else {
        printf("Conta não está cadastrada!");
        return;
    }
}

void saque(struct Cadastro vc[], int qtdCadastro, int numConta){
    int pos = buscaContaNum(vc, qtdCadastro, numConta);
    double vlrSaque;

    if(pos < 0){
        printf("Conta não existe!");
        return;
    }

    printf("Digite o valor do saque: ");
    scanf("%lf", &vlrSaque);

    if(vc[pos].saldo >= vlrSaque){
        vc[pos].saldo -= vlrSaque;
    } else {
        printf("Saldo insulficiente!");
        return;
    }
}

void exibirContas(struct Cadastro vc[], int qtdCadastro){
    for(int i = 0; i < qtdCadastro; i++){
        printf("Conta %d\n", i + 1);
        printf("Número da conta: %d\n", vc[i].numConta);
        printf("Nome do titular: %s\n", vc[i].nome);
        printf("Telefone: %s\n", vc[i].telefone);
    }
}