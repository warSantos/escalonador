#include "../headers/reporter.h"

void showTable(Processo *p, int tempoAtual, int legenda0, int legenda1, int legenda2){        
    
    if (legenda0) {
        
        printf("**************************************************************************************\n");
        printf("Estado do Sistema:\n");
        printf("**************************************************************************************\n");
        printf("TEMPO ATUAL: %d\n", tempoAtual);
        printf("PROCESSO EXECUTANDO:\n");
        printf("PID\tPPID\tPRIORIDADE\tVALOR\tTEMPO INI\tCPU USADA\n");
        printf("%d\t%d\t%d\t\t%d\t%d\t\t%d\n", p->pid, p->pidPai, p->prioridade, p->valorInteiro, p->tempoInicio, p->tempoAcumulado);
    }else {
                        
        if (legenda1 == 2) {
            
            
            if (legenda2) {
                
                printf("PROCESSO BLOQUEADO:\n");
                printf("PID\tPPID\tPRIORIDADE\tVALOR\tTEMPO INI\tCPU USADA\n");                
            }
            printf("%d\t%d\t%d\t\t%d\t%d\t\t%d\n", p->pid, p->pidPai, p->prioridade, p->valorInteiro, p->tempoInicio, p->tempoAcumulado);
        }else if (legenda1 == 3) {

            if(legenda2) {
                
                printf("PROCESSO PRONTOS:\n");
                printf("PID\tPPID\tPRIORIDADE\tVALOR\tTEMPO INI\tCPU USADA\n");                
            }
            printf("%d\t%d\t%d\t\t%d\t%d\t\t%d\n", p->pid, p->pidPai, p->prioridade, p->valorInteiro, p->tempoInicio, p->tempoAcumulado);
        }
    }    
    printf("**************************************************************************************\n");
}