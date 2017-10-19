/*
*  Arquivo 'main' para o modulo pmanager
*/

#include "../headers/pm.h"

#define L 10

int main(){        
    
    // Criando processo init.txt na tabela.
    manager = iniciaPM();
    Processo *temp = newProcesso(0, 0, 20, manager->tempoGeral, "Testes/init.txt");                
    addObj(manager->tabelaPcb, (void *)temp);                
    // copiando processo init.txt para cpu.
    //escalona(getObj(manager->tabelaPcb, 0), manager->cpu, 5);
        
    char inst;
    // Menu de indentificação dos comandos vindos do commander.
    while(read(0, &inst, 1)){    
        
        int newPid = fcfs();                
        if(newPid == -1){
                        
            printf("PM terminado.\n");   
            printf("Sachetoo cd seu 1 milhão?\n");
            exit(0);
        }
        
        trocaContexto(newPid , 2, 0);        
        //printf("PROCESSO %d ESCALONADO.\n", newPid);
        //printf("CONTADOR DE PROGRAMA %d.\n", ((Processo *)getObj(manager->tabelaPcb, newPid))->pc);
        printf("*********** %d - %c ************\n", manager->tempoGeral, inst);
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
            break;
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