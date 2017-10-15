/*
*  Arquivo 'main' para o modulo reporter
*/
#include "../headers/reporter.h"

int main(){
    
    Processo *temp = malloc(sizeof(Processo));
    sint size_sint = sizeof(sint);
    sint estado; // bloqueado 2, executando 0, pronto 1.
    sint true = 1, leg0, leg1;
    while(true){ // Enquanto existir dados a serem recebidos pelo pipe
        
        read(0, &temp->pid, size_sint);
        read(0, &temp->pidPai, size_sint);
        read(0, &temp->prioridade, size_sint);
        read(0, &temp->valorInteiro, sizeof(int));
        read(0, &temp->tempoAcumulado, size_sint);
        read(0, &estado, size_sint);
        read(0, &leg0, size_sint);
        true = read(0, &leg1, size_sint);
        
        // showTable(temp, estado, leg0, leg1);
    }
    return 0;
}