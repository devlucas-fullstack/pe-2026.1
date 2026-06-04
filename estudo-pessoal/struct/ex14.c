#include <stdio.h>
#include <string.h>

#define MAX_PASSAGEIROS 5
#define TAM 100

struct Voo {
    int codigoVoo;
    char destino[30];
    int vagasDisponiveis;
    float precoAssento;
};

struct BilheteVenda {
    int idVenda;
    int codigoVoo;                   // Código do voo escolhido pelo cliente
    int qtdPassageiros;              // Quantidade de pessoas nesta compra (máximo 5)
    char nomesPassageiros[MAX_PASSAGEIROS][40]; // Matriz de caracteres: nome de cada passageiro
    float valorTotalPago;
};

int main(){
    return 0;
}

int buscaVooPorCodigo(struct Voo v[], int tam, int codigoProcurado){
    for(int i = 0; i < tam; i++){
        if(v[i].codigoVoo == codigoProcurado){
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

void ordenaVoosPorDestino(struct Voo v[], int qtd){
    int i, j, menor;
    struct Voo aux;

    for(i = 0; i < qtd - 1; i++){
        menor = i;
        
        for(j = i + 1; j <= qtd - 1; j++){
            if(strcmp(v[j].destino, v[menor].destino) < 0){
                menor = j;
            }
        }

        aux = v[i];
        v[i] = v[menor];
        v[menor] = aux;
    }
}

int buscaBinariaVenda(struct BilheteVenda v[], int tam, int idVendaProcurado){
    int inicio = 0, fim = tam - 1;

    while(inicio <= fim){
        int meio = inicio + (fim - inicio) / 2;

        if(v[meio].idVenda == idVendaProcurado){
            return meio;
        } else if(v[meio].idVenda > idVendaProcurado){
            fim = meio - 1;
        } else if(v[meio].idVenda < idVendaProcurado){
            inicio = meio + 1;
        }
    }

    return -1;
}

void emitirBilhete(struct BilheteVenda vv[], int *tamVendas, struct Voo vv_voos[], int tamVoos){
    int idVenda, codVoo, qtdPas;
    int pos = 0;
    float valorTotal = 0;
    char tempStr[40];

    if(*tamVendas >= TAM){
        printf("Limite de vendas atingido!");
        return;
    }

    printf("Digite o ID da venda: ");
    scanf("%d", &idVenda);
    lerStr(tempStr, 40);

    pos = buscaBinariaVenda(vv, *tamVendas, idVenda);

    if(pos != -1){
        printf("ID de venda já existe!");
        return;
    }

    printf("Digite o código de voo: ");
    scanf("%d", &codVoo);
    lerStr(tempStr, 40);

    pos = buscaVooPorCodigo(vv_voos, tamVoos, codVoo);

    if(pos == -1){
        printf("Código de voo não existe!");
        return;
    }

    do{
        printf("Digite a quantidade de passageiros: ");
        scanf("%d", &qtdPas);
        lerStr(tempStr, 40);
    } while(qtdPas < 1 || qtdPas > MAX_PASSAGEIROS);

    if(vv_voos[pos].vagasDisponiveis < qtdPas){
        printf("Quantidade de vagas disponiveis: %d", vv_voos[pos].vagasDisponiveis);
        return;
    }

    for(int i = 0; i < qtdPas; i++){
        printf("Digite o nome do passageiro %d: ", i + 1);
        lerStr(vv[*tamVendas].nomesPassageiros[i], 40);
    }

    valorTotal = vv_voos[pos].precoAssento * qtdPas;
    vv_voos[pos].vagasDisponiveis -= qtdPas;

    vv[*tamVendas].idVenda = idVenda;
    vv[*tamVendas].codigoVoo = codVoo;
    vv[*tamVendas].qtdPassageiros = qtdPas;
    vv[*tamVendas].valorTotalPago = valorTotal;

    *tamVendas += 1;
}

void relatorioVendasDestino(struct BilheteVenda vv[], int tamVendas, struct Voo vv_voos[], int tamVoos, char destinoProcurado[]){
    int pos = 0;
    
    for(int i = 0; i < tamVendas; i++){
        pos = buscaVooPorCodigo(vv_voos, tamVoos, vv[i].codigoVoo);

        if(strcmp(vv_voos[pos].destino, destinoProcurado) == 0){
            printf("ID da venda: %d", vv[i].idVenda);
            printf("Código do voo: %d", vv[i].codigoVoo);

            for(int j = 0; j < vv[i].qtdPassageiros; j++){
                printf("Passageiro %d: %s", j + 1, vv[i].nomesPassageiros[j]);
            }
        } 
    }
}