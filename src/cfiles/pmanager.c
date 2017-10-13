/*
*  Arquivo 'main' para o modulo pmanager
*/

#include "../headers/pm.h"


int main(){
        
    manager = iniciaPM();
    Processo *temp = newProcesso(0, 0, 20, 0, "Testes/init.txt");    
    
    addObj((void *)manager->tabelaPcb, (void *)temp);
    temp = NULL;    
    
    temp = getObj(manager->tabelaPcb, 0);
    showP(temp);
    char inst;
    
    while(read(0, &inst, 1)){
        
        printf("inst: %c\n", inst);        
        
        
        
        if(inst == 'T'){ // se for solicitaado o 
                         //encerramento do programa
            break;
        }
    }   
    
    return 0;
}