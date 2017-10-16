/*
*  Arquivo 'main' para o modulo reporter
*/
#include "../headers/reporter.h"

int main(){
    
    Processo *temp = malloc(sizeof(Processo));
    sint size_sint = sizeof(sint);    
    sint bool = 1, leg0, leg1, leg2, cont = 0, tG;    
    while((bool = read(0, &tG, size_sint)) > 0){ // Enquanto existir dados a serem recebidos pelo pipe
        
        
        read(0, &temp->pid, size_sint);       
        read(0, &temp->pidPai, size_sint);
        read(0, &temp->prioridade, size_sint);
        bool = read(0, &temp->valorInteiro, sizeof(int));                
        read(0, &temp->tempoInicio, size_sint);
        read(0, &temp->tempoAcumulado, size_sint);        
        read(0, &leg0, size_sint);
        read(0, &leg1, size_sint);
        read(0, &leg2, size_sint);                                       
        //showP2(temp);
        cont++;
        db
        printf("temp %p\n", temp);
        // aqui vai a função showTable        
        showTable(temp, tG, leg0, leg1, leg2);
    }
    
    //exit(0);
    return 0;
}