/*
* Estrutura de dados necessárias para simular o Process Manager. 
*/

#ifndef process_manager_H
#define process_manager_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

// Utilização de short int para economia de memória.
typedef short int sint; 

// Estrutura com instrução e dados.
typedef struct tadInst {
    
    char instrucao;
    char *dados;
} TadInst;

// Esse tipo de dados tem a intenção de realizar a simulação da CPU física no programa.
typedef struct processador {
    
    sint pInst; // ponteiro para o array de instruções do programa.
    sint pc; // Contador atual do programa.
    int valorInteiro; // variável utilizada para realizar os calculos de simulação.
    sint tempoLimite; // conta o tempo limite que um programa tem para executar.
    sint tempoCorrente; // tempo variável (varia de 0 ao limite de tempo que tem um programa).
    TadInst *vetorInst; // vetor com instruções do processo.
        
}Cpu;

// Contem a estrutura de dados necessária para simular um processo.
typedef struct processo {
    
    sint pid; // id do processo.
    sint pidPai;
    sint pc; // ponteiro para array que contem as instruções do programa.
    int valorInteiro; // valor utilizado para gerar calculos de simulação do programa.
    sint prioridade; // coeficiente prioridade do processo na fila de espera dos processo.
    sint tempoInicio; // falta especificar melhor.
    sint tempoAcumulado; // soma de todo tempo gasto pelo processo na CPU.
    TadInst *vetorInst; // vetor com instruções do processo.
    
} Processo;

// Tipo de dado completo a para trabalhar o process manager.
typedef struct tadpm {
    
    sint tempoGeral;
    sint pidExec; // ponteiro (id) para o processo em execução.
    sint *pidPronto; // vetor com pids de processos prontos para execução.
    sint *pidBloq; // vetor com pids de processos bloqueados.
    Cpu *cpu; // estrutura que simula o processador físico.
    Processo *tabPcb; // tabela que armazena os processos e sua informaçoẽs
} TadPm;

// Iniciar vetor de instruções
TadInst *iniciaTad();

// Inicia (retorna) cpu virtual.
Cpu *iniciaCpu();

// Retorna uma nova célula do Tipo processo com os dados preenchidos.
Processo *criaProcesso(sint pid, sint pidPai, 
        sint prioridade, sint tempoInicio, TadInst *vInst);

// Iniciar a estrutura do process manager.
TadPm *iniciaPM();

#endif
