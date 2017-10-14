/*
*  Arquivo 'main' para o modulo pmanager
*/

#include "../headers/pm.h"

#define L 5

int main(){
        
    manager = iniciaPM();
    int j;
    Processo *temp;
    
    printf("\n");
    char *arq = malloc(sizeof(char)*50);
    for(j = 0; j < L; ++j){
        
        sprintf(arq, "Testes/%d.txt", j + 1);
        printf("%s\n", arq);
        temp = newProcesso(0, 0, 20, 0, arq);                
        addObj((void *)manager->tabelaPcb, (void *)temp);
        temp = NULL;
        
    }
    
    for(j = 0; j < L; ++j){
        
        temp = getObj(manager->tabelaPcb, j);
        printf("pmnger.c\n");
        showP(temp);
    }
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