#include "../headers/reporter.h"


void showTable(Processo *p, sint legenda0, sint legenda1,sint aux ,sint aux1){
if(legenda0 == 1){
	printf("**************************************************************************************\n");
	printf("Estado do Sistema:\n");
	printf("**************************************************************************************\n");
	printf("TEMPO ATUAL:%d\n",/*variavel que ta faltando*/ );
}
else if(legenda0 == 0){
	if(legenda1 == 1){
		printf("PROCESSO EXECUTANDO:\n");
		printf("PID\tPPID\tPRIORIDADE\tVALOR\tTEMPO INI\tCPU USADA\n");
		printf("%d\t%d\t%d\t%d\t%d\t%d\n",p->pid,p->pidPai,p->prioridade,p->valorInteiro,p->tempoInicio,p->tempoAcumulado);
	}
	if(legenda1 == 2){
		if(aux = 1){
			printf("PROCESSO BLOQUEADO:");
			printf("PID\tPPID\tPRIORIDADE\tVALOR\tTEMPO INI\tCPU USADA\n");
			aux = 0;
		}	
		printf("%d\t%d\t%d\t%d\t%d\t%d\n",p->pid,p->pidPai,p->prioridade,p->valorInteiro,p->tempoInicio,p->tempoAcumulado);
	}
	if(legenda1 == 3){
		if(aux1 ==1){
			printf("PROCESSO PRONTOS:");
			printf("PID\tPPID\tPRIORIDADE\tVALOR\tTEMPO INI\tCPU USADA\n");
			aux1 = 0;
		}
		printf("%d\t%d\t%d\t%d\t%d\t%d\n",p->pid,p->pidPai,p->prioridade,p->valorInteiro,p->tempoInicio,p->tempoAcumulado);
	}
}

}