/*
* Estrutura de dados necessárias para simular o Process Manager. 
*/

#ifndef process_manager_H
#define process_manager_H

#include "arraylist.h"
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define TAM 15


// Utilização de short int para economia de memória.
typedef short int sint; 

// Estrutura com instrução e dados.
typedef struct tadInst {
    
    char *instrucao; // vetor com as informações.
    char **dados; // matriz de string para salvar nome de arquivos e valores de variávies.
    sint size; // salva o tamanho do vetor.
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
    sint tempoInicio; // falta especificar melhor. (colocaremos como a primeira entrada na cpu).
    sint tempoAcumulado; // soma de todo tempo gasto pelo processo na CPU.
    TadInst *vetorInst; // vetor com instruções do processo.
    
} Processo;

// Tipo de dado completo a para trabalhar o process manager.
typedef struct tadpm {
    
    sint tempoGeral; // tempo geral do sistema (quantidade de instruções dadas pelo commander).
    sint pidExec; // ponteiro (id) para o processo em execução.
    sint *pidPronto; // vetor com pids de processos prontos para execução.
    sint *pidBloq; // vetor com pids de processos bloqueados.
    Cpu *cpu; // estrutura que simula o processador físico.
    Arraylist *tabelaPcb; // vetor que armazena os processos e sua informaçoẽs
} TadPm;

// Ponteiro global para estruturas utilizadas pelo process manager.
TadPm *manager;
// manager->pidPtonto[i]

// Iniciar vetor de instruções
TadInst *iniciaTadInst(sint size);

// Copia as instruções de um vetor de instruções para outro
void copiaInstrucao(TadInst *destino, TadInst *origem);

// Inicia (retorna) cpu virtual.
Cpu *iniciaCpu();

// Retorna uma nova célula do Tipo processo com os dados preenchidos.
Processo *newProcesso(sint pid, sint pidPai, 
        sint prioridade, sint tempoInicio, char *arquivo);

// Iniciar a estrutura do process manager.
TadPm *iniciaPM();

// Le as intruções do arquivo de um Processo e retorna um TadInst
TadInst *criaVetorInst(char *arquivo);

// Retira um processo da fila de bloqueados e move para o estado de pronto.
int unblock(sint *bloq, sint *pronto,  int size);

// Move um processo da cpu para fila de bloqueados.
void block(sint *bloq, sint *pronto, sint pid);

// copia dados de um processo da tabela para a cpu. 
void escalona(Processo *p, Cpu *cpu, sint tempoAloc);

// Retira o processo da cpu e atualiza ele na tabelaPcb.
void retiraP(Processo *p, Cpu *cpu);

// Realiza troca de contexto.
void trocaContexto(sint pid, sint tempoAloc, sint interrupt);

// Executa as instruções de um processo na CPU.
void executaProcesso(Cpu *cpu);

// Envia um processo via pipe.
void sendP(Processo *p, sint leg0, sint leg1, sint leg2);

// Cria um fork e troca a imagem do fork para o reporter.
void callReporter();

// Herísticas de escalonamento

// Função de ultimo recurso.
// Se todos os processos na fila de pronto terminar,
// tenta desbloquear um processo ou retornar o processo na cpu
// e em último caso -1.
int retPBloq(sint size);

// Função de comparação, retorna 1 se p1 > 2
// e zero se p1 <= p2.
int compare(int p1, int p2);

// Fila, preferência pelo primeiro processo adicionado na tabela.
int fcfs();

// Fila circular.
int roundRobin(sint posicao);

// define uma regra para estabelecer a prioridade de um
// processo, a principio e utilizado o tamanho do processo
// como base para prioridade.
int definePrioridade(Processo *p);

// Escalonamento por prioridade estática,
// (não existe ateração de prioridades).
// Parâmetro base define o limite superior ou inferior
// para inicio de cálculo.
int priStatic(sint base);

// Escalonamento por prioridade dinâmica,
// (as prioiridades são alteradas ao longo da execução).
// Parâmetro base define o limite superior ou inferior
// para inicio de cálculo.
// Valor de alteração definido no parâmetro reajuste.
int priDinamic(sint base, sint reajuste);

//RoundRobin
int rr(sint *posicao);

//prioridade
int prioridade();

//dando as prioridades para os processos
int prioridaderandom();
int prioridadetamanho();

// Funções de/para debug

void showP2(Processo *p);

void ptr(Processo *t);

// Imprimi a estrutura completa de um processo.
void showP(Processo *p);

// Imprime as instruções e seus respectivos dados.
// Informa a quantidade de instruções do processo.
void showInst(TadInst *t);


#endif
