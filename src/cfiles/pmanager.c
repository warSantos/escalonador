/*
*  Arquivo 'main' para o modulo pmanager
*/

#include "../headers/pm.h"

#define L 5

int main(){
    
    // #### debug do arraylist e da função copiaProcesso. 1. ###
    
    manager = iniciaPM();
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
    char inst;
    sint cont = 0;
    // Menu de indentificação dos comandos vindos do commander.
    while(read(0, &inst, 1)){
        
        printf("inst: %c %hu\n", inst, cont);       
        
        if(inst == 'Q'){ // executa a próxima instrução de um processo.
            
            executaProcesso(manager->cpu);
        }else if(inst == 'U'){ // Desbloqueia um processo bloqueado.
            
            unblock(manager->pidBloq, manager->pidPronto, manager->pidExec);
        }else if(inst == 'P'){ // chama o reporter.
            
            callReporter();            
        }else if(inst == 'T'){ // chama o reporter e encerra o programa.
            
            callReporter();
            break;
        }else{
            
            //printf("Instrução: %c linha: %hu, ignorada!\n", inst , cont + 1);
        }  
        cont++;
    }       
    return 0;
}