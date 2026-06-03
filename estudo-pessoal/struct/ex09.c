#include <string.h>
#include <stdio.h>

#define TAM_STRING 50
#define MAX_MEDICOS 30
#define MAX_CONSULTAS 100

struct Medico {
    int crm;
    char nome[TAM_STRING];
    float valorConsulta;
};

struct Consulta {
    int idConsulta;
    int crmMedico;
    char nomePaciente[TAM_STRING];
    int idadePaciente;
};

void lerStr(char str[], int tamMax);
void cadastrarMedico(struct Medico vm[], int *qtdM);
void realizarAgendamento(struct Consulta vc[], int *qtdC, struct Medico vm[], int qtdM);
void imprimirRelatorioConsultas(struct Consulta vc[], int qC, struct Medico vm[], int qM);
void ordenarConsultasPorPaciente(struct Consulta v[], int qtd);

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

void cadastrarMedico(struct Medico vm[], int *qtdM){
    int crm;
    char tempStr[TAM_STRING];

    printf("\n-----CADASTRA MÉDICO-----\n");

    if(*qtdM >= MAX_MEDICOS){
        printf("Quantidade de médicos cadastrados já está cheia!");
        return;
    }

    printf("\nDigite o CRM: ");
    scanf("%d", &crm);

    for(int i = 0; i < *qtdM; i++){
        if(vm[i].crm == crm){
            printf("CRM já foi cadastrado!");
            return;
        }
    }

    vm[*qtdM].crm = crm;

    lerStr(tempStr, TAM_STRING);
    printf("Digite o nome: ");
    lerStr(vm[*qtdM].nome, TAM_STRING);

    printf("Digite o valor da consulta: ");
    scanf("%f", &vm[*qtdM].valorConsulta);

    *qtdM += 1;
}

void realizarAgendamento(struct Consulta vc[], int *qtdC, struct Medico vm[], int qtdM){
    int crm, achouMedico = 0;
    char tempStr[TAM_STRING];

    printf("\n-----AGENDAMENTO-----\n");

    printf("Digite o CRM do médico: ");
    scanf("%d", &crm);

    for(int i = 0; i < qtdM; i++){
        if(vm[i].crm == crm){
            achouMedico = 1;
            break;
        }
    }

    if(achouMedico == 1){
        vc[*qtdC].crmMedico = crm;
    } else {
        printf("Médico não cadastrado!");
        return;
    }

    lerStr(tempStr, TAM_STRING);
    printf("Nome do paciente: ");
    lerStr(vc[*qtdC].nomePaciente, TAM_STRING);

    printf("Idade do paciente: ");
    scanf("%d", &vc[*qtdC].idadePaciente);

    vc[*qtdC].idConsulta = *qtdC + 1;

    *qtdC += 1;
}

void imprimirRelatorioConsultas(struct Consulta vc[], int qC, struct Medico vm[], int qM){
    float valorDesconto = 0;
    int iMedico;

    printf("\n-----IMPRESSÃO DE RELATÓRIOS DE CONSULTAS-----\n");

    for(int i = 0; i < qC; i++){
        printf("Consulta %d\n", i + 1);

        printf("Nome do paciente: %s\n", vc[i].nomePaciente);
        printf("Idade do paciente: %d\n", vc[i].idadePaciente);
        
        for(int j = 0; j < qM; j++){
            if(vc[i].crmMedico == vm[j].crm){
                iMedico = j;
            }
        }

        printf("Nome do médico: %s\n", vm[iMedico].nome);

        if(vc[i].idadePaciente >= 60){
            valorDesconto = vm[iMedico].valorConsulta * 0.8;
            printf("Valor da consulta: %.2f\n", valorDesconto);
        } else {
            printf("Valor da consulta: %.2f\n", vm[iMedico].valorConsulta);
        }
    }
}

void ordenarConsultasPorPaciente(struct Consulta v[], int qtd){
    printf("\n-----ORDENA CONSULTAS POR ORDEM ALFABÉTICA-----\n");

    int i, j, menor;
    struct Consulta aux;

    for(i = 0; i < qtd - 1; i++){
        menor = i;
        
        for(j = i + 1; j <= qtd - 1; j++){
            if(strcmp(v[j].nomePaciente, v[menor].nomePaciente) < 0){
                menor = j;
            }
        }

        aux = v[i];
        v[i] = v[menor];
        v[menor] = aux;
    }
}

int buscaBinariaMedico(struct Medico v[], int qtd, int crmProcurado){
    printf("\n-----BUSCA BINÁRIA-----\n");

    int inicio = 0, fim = qtd - 1;

    while(inicio <= fim){
        int meio = inicio + (fim - inicio) / 2;

        if(v[meio].crm == crmProcurado){
            return meio;
        } else if(v[meio].crm > crmProcurado){
            fim = meio - 1;
        } else if(v[meio].crm < crmProcurado){
            inicio = meio + 1;
        }
    }

    return -1;
}