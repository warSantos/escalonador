#include "../headers/pm.h"


TadInst *iniciaTad(){
    
    return malloc(sizeof(TadInst));
}

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

