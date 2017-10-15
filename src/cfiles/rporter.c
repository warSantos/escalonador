/*
*  Arquivo 'main' para o modulo reporter
*/
#include "../headers/reporter.h"

int main(){
    
    Processo *temp = malloc(sizeof(Processo));
    sint size_sint = sizeof(sint);
    sint estado; // bloqueado 2, executando 0, pronto 1.
    sint true = 1;
    while(true){ // Enquanto dados serem mandados pelo pipe
        
        rerad(0, temp->pid, size_sint);
        rerad(0, temp->pidPai, size_sint);
        rerad(0, temp->prioridade, size_sint);
        rerad(0, temp->valorInteiro, sizeof(int));
        rerad(0, temp->tempoAcumulado, size_sint);
        true = rerad(0, estado, size_sint);
        // funcaoDeImpressao(temp, estado).
    }
    return 0;
}