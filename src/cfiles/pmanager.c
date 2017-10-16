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
    escalona(getObj(manager->tabelaPcb, 0), manager->cpu, 5);
        
    char inst;
    // Menu de indentificação dos comandos vindos do commander.
    while(read(0, &inst, 1)){
        
        //printf("inst: %c %hu\n", inst, manager->tempoGeral);       
        
        if(inst == 'Q'){ // executa a próxima instrução de um processo.
            
            executaProcesso(manager->cpu);
        }else if(inst == 'U'){ // Desbloqueia um processo bloqueado.
            
            unblock(manager->pidBloq, manager->pidPronto, manager->pidExec);
        }else if(inst == 'P'){ // chama o reporter.
            db
            callReporter();            
        }else if(inst == 'T'){ // chama o reporter e encerra o programa.
            
            callReporter();
            break;
        }else{
            
            //printf("Instrução: %c linha: %hu, ignorada!\n", inst , cont + 1);
        }
        // aqui entra a política de escalonamento.
        // se for hora de escalonar um processo
            // então escalona.
        manager->tempoGeral++;
    }       
    return 0;
}

/*  DEBUG IMPORTANTE PARA ENVIO DE DADOS PELO PIPE.
 * // #### debug do arraylist e da função copiaProcesso. 1. ###
    sint j;
    Processo *temp;
    
    printf("\n");
    char *arq = malloc(sizeof(char)*50);
    
    for(j = 0; j < L; ++j){
        
        sprintf(arq, "Testes/%d.txt", j + 1);
        printf("%s\n", arq);
        temp = newProcesso(j, j+1, 20 - j, manager->tempoGeral, arq);                
        addObj((void *)manager->tabelaPcb, (void *)temp);
        temp = NULL;
        
    }
    
    for(j = 0; j < L; ++j){
        
        temp = getObj(manager->tabelaPcb, j);                
        //showP(temp);        
    }
    
    // ### Fim do código de debug ### 1.
    */