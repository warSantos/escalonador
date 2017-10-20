/*
*  Arquivo 'main' para o modulo reporter
*/
#include "../headers/reporter.h"

int main(){
    
    Processo *temp = malloc(sizeof(Processo));
    int size_int = sizeof(int);    
    int bool = 1, leg0, leg1, leg2, cont = 0, tG;    
    while((bool = read(0, &tG, size_int)) > 0){ // Enquanto existir dados a serem recebidos pelo pipe
        
        
        read(0, &temp->pid, size_int);       
        read(0, &temp->pidPai, size_int);
        read(0, &temp->prioridade, size_int);
        read(0, &temp->valorInteiro, sizeof(int));                
        read(0, &temp->tempoInicio, size_int);
        read(0, &temp->tempoAcumulado, size_int);        
        read(0, &leg0, size_int);
        read(0, &leg1, size_int);
        read(0, &leg2, size_int);                                               
        cont++;               
        
        showTable(temp, tG, leg0, leg1, leg2);
    }        
    return 0;
}