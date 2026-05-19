#include <stdio.h>
#include <string.h>

#define TAM_STRING 50
#define QTD_CONTAS 3

struct Conta{
    int numConta;
    char nome[TAM_STRING];
    int cpf;
    int telefone;
    double saldo;
};

void lerStr(char str[], int tamMax);
int busca(struct Conta c[], int numeroConta, int tam);
void cadastra(struct Conta c[], int numeroConta, int tam);
void exibeSaldo(struct Conta c[], int numeroConta, int tam);
void deposito(struct Conta c[], int numeroConta, int tam);
void saque(struct Conta c[], int numeroConta, int tam);
void exibeContas(struct Conta c[], int tam);
void menu(struct Conta cp[], struct Conta cc[], int *tamC, int *tamP);

int main(){
    struct Conta contaPoupanca[QTD_CONTAS];
    struct Conta contaCorrente[QTD_CONTAS];

    int tamCorrente = 0;
    int tamPoupanca = 0;

    menu(contaPoupanca, contaCorrente, &tamCorrente, &tamPoupanca);

    return 0;
}

void menu(struct Conta cp[], struct Conta cc[], int *tamC, int *tamP){
    int opcao, tipoConta, numConta;

    do {
        printf("\n-----banco-----\n");
        printf("1 - Cadastrar conta\n");
        printf("2 - Exibir saldo\n");
        printf("3 - Depósito\n");
        printf("4 - Saque\n");
        printf("5 - Exibir contas\n");
        printf("Escolha(0 p/ sair): ");
        scanf("%d", &opcao);

        if(opcao != 0){
            printf("\n1 - Conta corrente\n");
            printf("2 - Conta poupança");
            scanf("%d", &tipoConta);
        }

        switch(opcao){
            case 1:
                printf("Digite o número da conta: ");
                scanf("%d", &numConta);

                if(tipoConta == 1){
                    cadastra(cc, numConta, *tamC);
                    (*tamC)++;
                } else {
                    cadastra(cp, numConta, *tamP);
                    (*tamP)++;
                }
                break;
            case 2:
                printf("Digite o número da conta: ");
                scanf("%d", &numConta);

                if(tipoConta == 1){
                    exibeSaldo(cc, numConta, *tamC);
                } else {
                    exibeSaldo(cp, numConta, *tamP);
                }
                break;
            case 3:
                printf("Digite o número da conta: ");
                scanf("%d", &numConta);

                if(tipoConta == 1){
                    deposito(cc, numConta, *tamC);
                } else {
                    deposito(cp, numConta, *tamP);
                }
                break;
            case 4:
                printf("Digite o número da conta: ");
                scanf("%d", &numConta);

                if(tipoConta == 1){
                    saque(cc, numConta, *tamC);
                } else {
                    saque(cp, numConta, *tamP);
                }
                break;
            case 5:
                if(tipoConta == 1){
                    exibeContas(cc, *tamC);
                } else {
                    exibeContas(cp, *tamP);
                }
                break;
        }

    } while(opcao != 0);
}

int busca(struct Conta c[], int numeroConta, int tam){
    if(tam == 0){
        return -1;
    }

    for(int i = 0; i < tam; i++){
        if(c[i].numConta == numeroConta){
            return i;
        }
    }

    return -2;
}

void cadastra(struct Conta c[], int numeroConta, int tam){
    int verificaNumConta = busca(c, numeroConta, tam);

    if(verificaNumConta != -2 && verificaNumConta != -1){
        printf("\nConta ja existe!");
        return;
    }

    c[tam].numConta = numeroConta;

    printf("\n-----cadastro-----\n");
    printf("Nome: \n");
    getchar();
    lerStr(c[tam].nome, TAM_STRING);
    printf("CPF: \n");
    scanf("%d", &c[tam].cpf);
    printf("Telefone: \n");
    scanf("%d", &c[tam].telefone);
    printf("Saldo: \n");
    scanf("%lf", &c[tam].saldo);
    
    printf("\nConta cadastrada com sucesso!\n");
}

void exibeSaldo(struct Conta c[], int numeroConta, int tam){
    int verificaNumConta = busca(c, numeroConta, tam);

    if(verificaNumConta != -2 && verificaNumConta != -1){
        for(int i = 0; i < tam; i++){
            if(c[i].numConta == numeroConta){
                printf("\n-----saldo da conta de numero %d-----\n", numeroConta);
                printf("%.2lf", c[i].saldo);
            }
        }
    } else {
        printf("\nConta não existe!");
        return;
    }
}

void deposito(struct Conta c[], int numeroConta, int tam){
    int pos = busca(c, numeroConta, tam);
    double valor;

    if(pos >= 0){
        printf("\n-----deposito-----\n");
        printf("Digite o valor do depósito: \n");
        scanf("%lf", &valor);
        c[pos].saldo += valor;
    } else {
        printf("\nConta não existe!");
        return;
    }
}

void saque(struct Conta c[], int numeroConta, int tam){
    int pos = busca(c, numeroConta, tam);
    double valor;

    if(pos >= 0){
        printf("\n-----saque-----\n");
        printf("Digite o valor do saque: \n");
        scanf("%lf", &valor);
        if(valor > c[pos].saldo){
            printf("\nSaldo insuficiente!");
            return;
        } else {
            c[pos].saldo -= valor;
        }
    } else {
        printf("\nConta não existe!");
        return;
    }
}

void exibeContas(struct Conta c[], int tam){
    printf("\n-----exibe contas-----\n");    

    if(tam == 0){
        printf("Nenhuma conta cadastrada!");
        return;
    }

    for(int i = 0; i < tam; i++){
        printf("\n----conta %d-----\n", i + 1);
        printf("Número da conta: %d\n", c[i].numConta);
        printf("Nome: %s\n", c[i].nome);
        printf("Telefone: %d\n", c[i].telefone);
    }
}

void lerStr(char str[], int tamMax){
    fgets(str, tamMax, stdin);

    int tam = strlen(str);

    if(tam > 0 && str[tam - 1] == '\n'){
        str[tam - 1] = '\0';
    }
}