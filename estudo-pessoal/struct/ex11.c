#include <stdio.h>
#include <string.h>

#define MAX_MEDICOS 20
#define MAX_CONSULTAS 100
#define TAM_STRING 50

struct Medico {
    int crm;
    char nome[TAM_STRING];
    char especialidade[TAM_STRING];
    float valorBase;
};

struct Consulta {
    int idConsulta;
    int crmMedico; // Relacionado ao crm da struct Medico
    char tipoAtendimento; // 'E' para Eletiva, 'U' para Urgência
    int distanciaKM; // Distância que o médico precisará deslocar (se for 0, é Online)
    float valorFinal; // Será calculado pelo sistema
};

int buscaCRM(struct Medico vm[], int qtdM, int x){
    for(int i = 0; i < qtdM; i++){
        if(vm[i].crm == x){
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

void cadastrarConsulta(struct Consulta vc[], int *qtdC, struct Medico vm[], int qtdM){
    int crm, pos;
    char tipoAt;
    float valor = 0;
    char tempStr[TAM_STRING];

    if(*qtdC >= MAX_CONSULTAS){
        printf("Limite de consultas atingido!");
        return;
    }

    printf("Digite o CRM do médico: ");
    scanf("%d", &crm);
    lerStr(tempStr, TAM_STRING);

    pos = buscaCRM(vm, qtdM, crm);

    if(pos != -1){
        do{
            printf("Digite o tipo de atendimento(E/U): ");
            scanf(" %c", &tipoAt);
        }while(tipoAt != 'E' && tipoAt != 'U');

        printf("Digite a distância em KM: ");
        scanf("%d", &vc[*qtdC].distanciaKM);
        lerStr(tempStr, TAM_STRING);

        valor = vm[pos].valorBase;

        if(tipoAt == 'U'){
            valor = valor * 1.20;
        }

        if(vc[*qtdC].distanciaKM > 0){
            valor = valor + (vc[*qtdC].distanciaKM * 2.50);
        }

        vc[*qtdC].crmMedico = crm;
        vc[*qtdC].tipoAtendimento = tipoAt;
        vc[*qtdC].valorFinal = valor;
    } else {
        printf("Médico não cadastrado!");
        return;
    }

    vc[*qtdC].idConsulta = *qtdC + 1;
    *qtdC += 1;
}

void listarMedicosPorEspecialidade(struct Medico vm[], int qtdM, char espProcurada[]){
    int achou = 0;

    for(int i = 0; i < qtdM; i++){
        if(strcmp(vm[i].especialidade, espProcurada) == 0){
            printf("CRM: %d", vm[i].crm);
            printf("Nome: %s", vm[i].nome);
            achou++;
        }
    }

    if(achou == 0){
        printf("Nenhum medico encontrado para esta espacialidade!");
    }
}

void ordenarConsultasPorValor(struct Consulta vc[], int qtdC){
    int i, j, menor;
    struct Consulta aux;

    for(i = 0; i < qtdC - 1; i++){
        menor = i;

        for(j = i + 1; j <= qtdC - 1; j++){
            if(vc[j].valorFinal > vc[menor].valorFinal){
                menor = j;
            }
        }

        aux = vc[i];
        vc[i] = vc[menor];
        vc[menor] = aux;
    }
}

void gerarRelatorioFaturamento(struct Consulta vc[], int qC, struct Medico vm[], int qM){
    int pos;
    float fat = 0;
    float somaKm = 0, mediaKm = 0;
    int atPresencial = 0;

    for(int i = 0; i < qC; i++){
        printf("ID da consulta: %d", vc[i].idConsulta);

        if(vc[i].tipoAtendimento == 'U'){
            printf("Tipo de atendimento: Urgência");
        } else {
            printf("Tipo de atendimento: Eletiva");
        }

        pos = buscaCRM(vm, qM, vc[i].crmMedico);

        printf("Nome do médico: %s", vm[pos].nome);

        printf("Valor final: %.2f", vc[i].valorFinal);

        fat += vc[i].valorFinal;

        if(vc[i].distanciaKM > 0){
            somaKm += vc[i].distanciaKM;
            atPresencial++;
        }
    }

    if(atPresencial > 0){
        mediaKm = somaKm / atPresencial;
    } else {
        mediaKm = 0;
    }

    printf("Faturamento total: %.2f", fat);
    printf("Média de KM rodados: %.2f", mediaKm);
}