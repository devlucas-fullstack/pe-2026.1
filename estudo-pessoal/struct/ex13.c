#include <stdio.h>
#include <string.h>

#define MAX_SERVICOS 5
#define TAM 100

struct Mecanico {
    int idMecanico;
    char nome[40];
    char especialidade[30];
    float valorHora;
};

struct OrdemServico {
    int idOS;
    int idMecanico;
    int qtdServicos;                    // Quantidade de serviços feitos na OS (máximo 5)
    int codigosServicos[MAX_SERVICOS];  // Vetor com os códigos dos serviços realizados
    int horasTrabalhadas[MAX_SERVICOS]; // Vetor com as horas gastas em cada serviço respectivo
    float valorTotal;
};

int main(){
    return 0;
}

int buscaMecanicoId(struct Mecanico v[], int tam, int idProcurado){
    for(int i = 0; i < tam; i++){
        if(v[i].idMecanico == idProcurado){
            return i;
        }
    }

    return -1;
}

void ordenaOSPorId(struct OrdemServico v[], int qtd){
    int i, j, fim, pos, troca;
    struct OrdemServico aux;

    troca = 1;
    fim = qtd - 2;
    pos = 0;

    while(troca == 1){
        troca = 0;

        for(i = 0; i <= fim; i++){
            if(v[i].idOS > v[i + 1].idOS){
                aux = v[i];
                v[i] = v[i + 1];
                v[i + 1] = aux;

                troca = 1;
                pos = i;
            }
        }

        fim = pos - 1;
    }
}

int buscaBinariaOS(struct OrdemServico v[], int tam, int idOSProcurado){
    int inicio = 0, fim = tam - 1;

    while(inicio <= fim){
        int meio = inicio + (fim - inicio) / 2;

        if(v[meio].idOS == idOSProcurado){
            return meio;
        } else if(v[meio].idOS > idOSProcurado){
            fim = meio - 1;
        } else if(v[meio].idOS < idOSProcurado){
            inicio = meio + 1;
        }
    }

    return -1;
}

void registrarOS(struct OrdemServico vo[], int *tamOS, struct Mecanico vm[], int tamMecanicos){
    int idOS, pos = 0, idMec, qtdServ, codServ, qtdHoras, somHoras = 0;
    float valorTotal = 0;

    if(*tamOS >= TAM){
        printf("Limite de ordem de serviço atingido!");
        return;
    }

    printf("Digite o ID da OS: ");
    scanf("%d", &idOS);

    pos = buscaBinariaOS(vo, *tamOS, idOS);

    if(pos != -1){
        printf("Ordem de serviço existe!");
        return;
    }

    printf("Digite o ID do mecânico: ");
    scanf("%d", &idMec);

    pos = buscaMecanicoId(vm, tamMecanicos, idMec);

    if(pos == -1){
        printf("Mecânico não existe!");
        return;
    }

    do{
        printf("Digite a quantidade de serviços: ");
        scanf("%d", &qtdServ);
    }while(qtdServ < 1 || qtdServ > MAX_SERVICOS);

    
    for(int i = 0; i < qtdServ; i++){
        printf("Digite o código do serviço: ");
        scanf("%d", &codServ);

        printf("Digite a quantidade de horas gastas: ");
        scanf("%d", &qtdHoras);

        somHoras += qtdHoras;

        int posAtual = vo[*tamOS].qtdServicos;
        vo[*tamOS].codigosServicos[i] = codServ;
        vo[*tamOS].horasTrabalhadas[i] = qtdHoras;
    }

    valorTotal = vm[pos].valorHora * somHoras;
    vo[*tamOS].valorTotal = valorTotal;
    vo[*tamOS].idOS = idOS;
    vo[*tamOS].idMecanico = idMec;
    vo[*tamOS].qtdServicos = qtdServ;

    *tamOS += 1;
}

void relatorioFaturamentoMecanico(struct OrdemServico vo[], int tamOS, int idMecanicoAlvo){
    float fat = 0;

    for(int i = 0; i < tamOS; i++){
        if(vo[i].idMecanico == idMecanicoAlvo){
            printf("---OS %d---", i + 1);
            printf("ID da OS: %d", vo[i].idOS);
            printf("Valor total: %.2f", vo[i].valorTotal);
            fat += vo[i].valorTotal;
        }
    }

    printf("Faturamento total: %.2f", fat);
}