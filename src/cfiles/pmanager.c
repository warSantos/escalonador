/*
*  Arquivo 'main' para o modulo pmanager
*/

#include "../headers/pm.h"

#define L 10
#define PRIO_INIT 100

int main(int argc, char **argv){                
    
    // Criando processo init.txt na tabela.
    manager = iniciaPM();
    Processo *temp = newProcesso(0, 0, 20, manager->tempoGeral, argv[2]);                        
    temp->prioridade = PRIO_INIT;
    addObj(manager->tabelaPcb, (void *)temp);                
    // copiando processo init.txt para cpu.
    //escalona(getObj(manager->tabelaPcb, 0), manager->cpu, 5);
        
    char inst;    
    int newPid = 0;
    // Menu de indentificação dos comandos vindos do commander.
    while(read(0, &inst, 1)){        
        
        //newPid = fcfs();                
        //newPid = fcfs(newPid);                
        //newPid = roundRobin(newPid);
        newPid = priStatic(0);        
        //newPid = priDinamic(0, -2);
        if(newPid == -1){
                                    
            callReporter();                 
            printf("*********** %d - %c ************\n", manager->tempoGeral, inst);
            return 0;
        }
        
        trocaContexto(newPid , 5, 0);                
        if(inst == 'Q'){ // executa a próxima instrução de um processo.
                        
            executaProcesso(manager->cpu);            
        }else if(inst == 'U'){ // Desbloqueia um processo bloqueado.
            
            if(unblock(manager->pidBloq, manager->pidPronto, manager->pidExec) == -1){
                
                //printf("SEM PROCESSOS NA FILA DE BLOQUEADO.\n");
            }
        }else if(inst == 'P'){ // chama o reporter.
                        
            callReporter();                 
        }else if(inst == 'T'){ // chama o reporter e encerra o programa.
            
            callReporter();            
            return 0;
        }else{
            
            printf("Instrução: %c linha: %hu, ignorada!\n", inst , manager->tempoGeral + 1);
        }
        // aqui entra a política de escalonamento.
        // se for hora de escalonar um processo
            // então escalona.        
        manager->tempoGeral++; 
    }       
    return 0;
}