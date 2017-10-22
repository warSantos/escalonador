/*
*  Arquivo 'main' para o modulo pmanager
*/

#include "../headers/pm.h"

#define PRIO_INIT 100 // define prioridade inicial do processo init.
#define QUANTUM 3 // define a quantidade de instruções por um Q.
#define ESC 1 // define qual algoritmo de escalonamento deve ser utilizado.
#define BASE 0 // define o o limite de comparação de prioridade
               // para o algoritmo de prioridade.
#define MINERA 1 // define se dever ser utilizada a função minera.

int main(int argc, char **argv){                
    
    // Criando processo init.txt na tabela.
    manager = iniciaPM();
    Processo *temp = newProcesso(0, 0, 20, manager->tempoGeral, argv[2]);
    temp->prioridade = PRIO_INIT;
    addObj(manager->tabelaPcb, (void *)temp);                
    // copiando processo init.txt para cpu.    
        
    char inst;    
    int newPid = 0;
    // Menu de indentificação dos comandos vindos do commander.
    while(read(0, &inst, 1)){        
        
        // escolhe processo a ser escalonado.
        if(ESC == 1){
            
            newPid = fcfs();
        }else if(ESC == 2){
            
            newPid = roundRobin(newPid);
        }else if(ESC == 3){
            
            newPid = priStatic(BASE);
        }        
        
        if(newPid == -1){
                              
            callReporter();
            if(MINERA){
                
                minera(argv[2], (char) (QUANTUM + 48));
            }
            return 0;
        }        
        // realiza troca de contexto.
        trocaContexto(newPid , QUANTUM);                
        if(inst == 'Q'){ // executa a próxima instrução de um processo.
                        
            executaProcesso(manager->cpu);            
        }else if(inst == 'U'){ // Desbloqueia um processo bloqueado.
            
            unblock(manager->pidBloq, manager->pidPronto, manager->pidExec);                
        }else if(inst == 'P'){ // chama o reporter.
                        
            callReporter();                 
        }else if(inst == 'T'){ // chama o reporter e encerra o programa.
            
            callReporter();            
            return 0;
        }else{
            
            if(MINERA){
                
                minera(argv[2], (char) (QUANTUM + 48));
            }
            printf("Instrução: %c linha: %d, ignorada!\n", inst , manager->tempoGeral + 1);
        }        
        manager->tempoGeral++; 
    }       
    return 0;
}