#include "../headers/reporter.h"
void reporter(TadPm T){
	int i,j;
	printf("****************************************************************\n");
	printf("Estado do sistema:\n");
	printf("****************************************************************\n");
	printf("TEMPO ATUAL:%d\n",T->tempoGeral);
	printf("PROCESSOS EXECUTANDO:\n");
	for(i=0;i<T->tadPcbsize;i++){
		if(T->tadPcb[i].pid == T->pidExec){
			printf("%d\t%d\t%d\t%d\t%d\t%d\n",T->tadPcb[i].pid,T->tadPcb[i].pidPai,T->tadPcb[i].prioridade,T->tadPcb[i].ValorInteiro,T->tadPcb[i].tempoInicio,T->tadPcb[i].tempoAcumulado);
		}
	}
	printf("BROQUEADO:\n");
	for(i=0;i<T->tadPcbsize;i++){
		for(j=0;j<T->pidBloqsize;j++){
			if(T->tadPcb[i].pid == T->pidBloq[j]){
				printf("%d\t%d\t%d\t%d\t%d\t%d\n",T->tadPcb[i].pid,T->tadPcb[i].pidPai,T->tadPcb[i].prioridade,T->tadPcb[i].ValorInteiro,T->tadPcb[i].tempoInicio,T->tadPcb[i].tempoAcumulado);
			}
		}
	}
	printf("PROCESSOS PRONTOS:\n");
	for(i=0;i<T->tadPcbsize;i++){
		for(j=0;j<T->pidProntosize;j++){
			if(T->tadPcb[i].pid == T->pidPronto[j]){
				printf("%d\t%d\t%d\t%d\t%d\t%d\n",T->tadPcb[i].pid,T->tadPcb[i].pidPai,T->tadPcb[i].prioridade,T->tadPcb[i].ValorInteiro,T->tadPcb[i].tempoInicio,T->tadPcb[i].tempoAcumulado);
			}
		}
	}
	printf("****************************************************************\n");
}
int main(){
	TadPm T;
	reporter(T);
	return 0;
}