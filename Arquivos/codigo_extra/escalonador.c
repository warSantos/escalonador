
// Escalonamento por prioridade dinâmica,
// (as prioiridades são alteradas ao longo da execução).
// Parâmetro base define o limite superior ou inferior
// para inicio de cálculo.
// Valor de alteração definido no parâmetro reajuste.
int priDinamic(int base, int reajuste);



int priDinamic(int base, int reajuste){
    
    int i, pid = -1;
    Processo *p;
    int size = getLast(manager->tabelaPcb), temp = base;    
    for(i = 0; i < size; ++i){
        
        if(manager->pidPronto[i] == 1){ 
                                                        
            p = getObj(manager->tabelaPcb, i);            
            if(compare(p->prioridade, temp)){
                
                temp = p->prioridade;
                pid = p->pid;
            }            
        }                
    } 
    
    if(pid > -1){ // reajustando a prioridade do processo pronto.
        
        if(p->pc > 0 
                && p->vetorInst->instrucao[p->pc] == 'B'){
            
            p->prioridade--;
        }else{
            p->prioridade += reajuste;
        }
        return pid;
    }
    // Se acabar os processos na fila de pronto 
    // tenta retornar um bloqueado ou manter o processo da cpu.
    if((pid = retPBloq(size)) > -1){ 
                // reajusta a prioridade do processo desbloqueado.
        
        p = getObj(manager->tabelaPcb, pid);        
        
        if(p->pc > 0
                && p->vetorInst->instrucao[p->pc] == 'B'){
            
            p->prioridade--;
        }else{
            p->prioridade += reajuste;
        }
    }            
    return pid;
}
