/*
*  Arquivo 'main' para o modulo reporter
*/
#include "../headers/reporter.h"

int main(){
    
    Processo *temp = malloc(sizeof(Processo));
    sint size_sint = sizeof(sint);    
    sint bool = 1, leg0, leg1, leg2, cont = 0, tG;    
    while(bool){ // Enquanto existir dados a serem recebidos pelo pipe
        
        read(0, &tG, size_sint);
        read(0, &temp->pid, size_sint);       
        read(0, &temp->pidPai, size_sint);
        read(0, &temp->prioridade, size_sint);
        read(0, &temp->valorInteiro, sizeof(int));
        read(0, &temp->tempoInicio, size_sint);
        read(0, &temp->tempoAcumulado, size_sint);
        read(0, &leg0, size_sint);
        read(0, &leg1, size_sint);
        bool = read(0, &leg2, size_sint);
        
        printf("\nP: %d bool %d", cont + 1, bool);
        showP(temp);        
        cont++;
        // aqui vai a função showTable
    }
    return 0;
}
/*
 read(0, &temp->tempoAcumulado, size_sint);
        read(0, &temp->tempoInicio, size_sint);
 */