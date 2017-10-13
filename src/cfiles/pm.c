#include "../headers/pm.h"


TadInst *iniciaTad(sint size){
        
    TadInst *temp = malloc(sizeof(TadInst));
    temp->dados = malloc(sizeof(char *) * size);    
    temp->size = size;
    return temp;
}

void copiaInstrucao(TadInst *destino, TadInst *origem){
    
    sint i;
    destino->instrucao = malloc(sizeof(char) * strlen(origem->instrucao) + 1);
    for(i = 0; i < origem->size; ++i){
        
        destino->instrucao[i] = origem->instrucao[i];        
        destino->dados[i] = malloc(sizeof(char) * strlen(origem->dados[i]) + 1);
        strcpy(destino->dados[i], origem->dados[i]);
    }
}
/*
 int i;
    for(i = 0; i < size; ++i){
        
        temp->dados[i] = malloc(sizeof(char)*15);
    }
 * 
 */
Cpu *iniciaCpu(){
    
    Cpu *temp = malloc(sizeof(Cpu));
    temp->pInst = 0;
    temp->pc = 0;
    temp->valorInteiro = 0;
    temp->tempoLimite = 0;
    temp->tempoCorrente = 0;
    temp->vetorInst = NULL;        
    return temp;
}

Processo *newProcesso(sint pid, sint pidPai,
        sint prioridade, sint tempoInicio, TadInst *vInst){

    Processo *temp = malloc(sizeof(Processo));
    temp->pid = pid;
    temp->pidPai = pidPai;
    temp->prioridade = prioridade;
    temp->tempoInicio = tempoInicio;
    temp->tempoAcumulado = 0;
    temp->vetorInst = vInst;
    return temp;
}

TadPm *iniciaPM(){

    TadPm *temp = malloc(sizeof(TadPm));
    temp->tempoGeral = 0;    
    temp->pidExec = 0;
    temp->cpu = iniciaCpu();  
    temp->tabelaPcb = newArray(sizeof(Processo));
    return temp;
}

 TadInst *criaVetorInst(char *arquivo){
    
    FILE *leitor = fopen(arquivo, "r");
    if(leitor == NULL){

        return (TadInst *)NULL;
    }    
    sint cont = 0, len;   
    TadInst *vInst = iniciaTad(TAM), *temp = NULL;    
    char buff[100];
    while(fscanf(leitor, "%c %s\n",&vInst->instrucao[cont], buff) != EOF){
        
        len = strlen(buff) + 1;
        vInst->instrucao = malloc(sizeof(char) * len);
        strcpy(vInst->dados[cont], buff);
        if(cont == vInst->size - 2){ // hora de allocar mais memória para o vetor.
                        
            vInst->size *= 2; 
            temp = iniciaTad(vInst->size);
            copiaInstrucao(temp, vInst);                       
            free(vInst);
            vInst = temp;
            temp = NULL;
        }                        
        cont++;               
    }    
    temp = iniciaTad(cont);
    copiaInstrucao(temp, vInst);
    free(vInst);
    vInst = temp;
    temp = NULL;
    vInst->size = cont;
    return vInst;
}
