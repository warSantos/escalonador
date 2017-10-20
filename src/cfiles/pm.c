#include "../headers/pm.h"
#include <unistd.h>

/* ### FUNÇÕES PARA INICIARLIZAR, COPIAR E MANNIPULAR OS TIPOS DE DADOS. ###*/

TadInst *iniciaTadInst(sint size){
            
    TadInst *temp = malloc(sizeof(TadInst));
    temp->instrucao = malloc(sizeof(char) * size);
    temp->dados = malloc(sizeof(char *) * size);    
    temp->size = size;
    return temp;
}

void copiaInstrucao(TadInst *destino, TadInst *origem){
    
    sint i;    
    for(i = 0; i < origem->size; ++i){
                
        destino->instrucao[i] = origem->instrucao[i];                
        destino->dados[i] = malloc(sizeof(char) * strlen(origem->dados[i]) + 1);
        strcpy(destino->dados[i], origem->dados[i]);        
    }    
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
        sint prioridade, sint tempoInicio, char *arquivo){

    Processo *temp = malloc(sizeof(Processo));
    temp->pid = pid;    
    manager->pidPronto[temp->pid] = 1;    
    temp->pidPai = pidPai;    
    temp->tempoInicio = tempoInicio;
    temp->tempoAcumulado = 0;
    temp->vetorInst = criaVetorInst(arquivo);
    if(temp->vetorInst == NULL){
        
        printf("Arquivo %s de processo não encontrado.\n", arquivo);
        return NULL;
    }    
    temp->prioridade = definePrioridade(temp);
    return temp;
}

TadPm *iniciaPM(){

    TadPm *temp = malloc(sizeof(TadPm));
    temp->tempoGeral = 0;    
    temp->pidExec = 0;
    temp->cpu = iniciaCpu();      
    temp->tabelaPcb = newArray(sizeof(Processo));    
    temp->pidPronto = calloc(sizeof(sint), getSize(temp->tabelaPcb));
    temp->pidBloq = calloc(sizeof(sint), getSize(temp->tabelaPcb));
    return temp;
}

TadInst *criaVetorInst(char *arquivo) {
       
    FILE *leitor = fopen(arquivo, "r");
    if (leitor == NULL) {
        
        return (TadInst *) NULL;
    }
    sint cont = 0, len;
    TadInst *vInst = iniciaTadInst(TAM), *temp = NULL;   
    char buff[20];
    while (fscanf(leitor, "%c %s\n", &vInst->instrucao[cont], buff) != EOF) {
        
        len = strlen(buff) + 1;
        vInst->dados[cont] = malloc(sizeof (char) * len);               
        strcpy(vInst->dados[cont], buff);        
        
        if (cont == vInst->size - 1) { // hora de allocar mais memória para o vetor.
                                       
            temp = iniciaTadInst(vInst->size * 2);            
            copiaInstrucao(temp, vInst);              
            free(vInst);
            vInst = temp;
            temp = NULL;
        }
        cont++;
        
    }  
    vInst->size = cont;  
    temp = iniciaTadInst(cont);
    copiaInstrucao(temp, vInst);    
    free(vInst);
    vInst = temp;
    temp = NULL;  
    return vInst;
}

/*### FUNÇÕES DE MANIPULAÇÃO DO PROCESSO. ###*/

int unblock(sint *bloq, sint *pronto, int size){
    
    int i = 0;
    while(!bloq[i] && i < size){
        
        ++i;
    }
    if(i < size){
                
        bloq[i] = 0; // desbloqueando o processo.
        pronto[i] = 1; // movendo ele para fila de pronto.
        return i;
    }
    return -1;
}

void block(sint *bloq, sint *pronto, sint pid){
    
    bloq[pid] = 1;
    pronto[pid] = 0;
}

void escalona(Processo *p, Cpu *cpu, sint quantum){
        
    cpu->pc = p->pc;
    cpu->valorInteiro = p->valorInteiro;
    cpu->tempoLimite = quantum;
    cpu->vetorInst = p->vetorInst;     
}

void retiraP(Processo *p, Cpu *cpu){
        
    p->pc = cpu->pc;
    p->valorInteiro = cpu->valorInteiro;
    p->tempoAcumulado += cpu->tempoCorrente;    
}

void trocaContexto(sint pid, sint quantum, sint interrupt){
    
    // removendo o processo da cpu e voltando ele para tabela
    Processo *p = getObj(manager->tabelaPcb, manager->pidExec);
    retiraP(p, manager->cpu);   
    if(manager->pidBloq[manager->pidExec] != 1 && 
            manager->pidPronto[manager->pidExec] != -1){
        
        manager->pidPronto[manager->pidExec] = 1;
    }    
    
    // escalonando o proximo processo.
    p = getObj(manager->tabelaPcb , pid);
    escalona(p, manager->cpu, quantum);
    manager->pidExec = pid;
    manager->pidPronto[manager->pidExec] = 0;
}

void executaProcesso(Cpu *cpu) {       
    
    Processo *temp = getObj(manager->tabelaPcb, manager->pidExec), *fk;    
    sint id;
    cpu->tempoCorrente = 0;    
    while(cpu->tempoCorrente < cpu->tempoLimite && cpu->pc < temp->vetorInst->size){
               
        switch (cpu->vetorInst->instrucao[cpu->pc]){//saber qual função sera executada
            case 'S'://valor inteiro é alterado
                
                cpu->valorInteiro = atoi(cpu->vetorInst->dados[cpu->pc]);                
                break;
            case 'A'://soma o valor inteiro com a entrada
                
                cpu->valorInteiro += atoi(cpu->vetorInst->dados[cpu->pc]);
                break;
            case 'D'://subtrai o valor inteiro com a entrada
                
                cpu->valorInteiro -= atoi(cpu->vetorInst->dados[cpu->pc]);
                break;
            case 'B'://bloqueia o processo voltando para o escalonador
                // aqui tbm deve ser chamada a função de troca de contexto.
                block(manager->pidBloq, manager->pidPronto, temp->pid);                
                cpu->pc++;
                cpu->tempoCorrente++;
                return;
            case 'E'://termina o processo simulado
                                
                manager->pidPronto[temp->pid] = -1;                
                temp->pc = cpu->pc; // atualizando pc antes para evitar no escalonamento.                
                cpu->tempoCorrente++;
                return;
            case 'F'://cria processo filho
                break;  
            case 'R'://abre um arquivo com nome passado e altera o valor inteiro para a primeira instrução do novo processo                                
                                
                id = getLast(manager->tabelaPcb);
                fk = newProcesso(id, temp->pid, 15, manager->tempoGeral,
                        temp->vetorInst->dados[cpu->pc]);                
                
                if(id < getSize(manager->tabelaPcb)){
                
                    addObj(manager->tabelaPcb, fk);
                }else{
                    
                    int bkp_size = getSize(manager->tabelaPcb);
                    if (addObj((void *) manager->tabelaPcb, (void *) fk)) {

                        manager->pidBloq = myrealloc(manager->pidBloq, bkp_size, getSize(manager->tabelaPcb), sizeof (sint));
                        manager->pidPronto = myrealloc(manager->pidPronto, bkp_size, getSize(manager->tabelaPcb), sizeof (sint));
                    }     
                }                
                break;
            default:
                printf("Comando inválido %c.\n", cpu->vetorInst->instrucao[cpu->pc]);
        }
        cpu->pc++;
        cpu->tempoCorrente++;        
    }            
}

int retPBloq(sint size){
    
    Processo *p;
    int i = unblock(manager->pidBloq, manager->pidPronto, size);
    if(i > -1){
                
        return i;
    }
    p = getObj(manager->tabelaPcb, manager->pidExec);
    if(p->vetorInst->instrucao[p->pc] == 'E'){
                        
        return -1;
    }    
    return p->pid;
}

int compare(int p1, int p2){
    
    if(p1 > p2){
        
        return 1;
    }else{
        
        return 0;
    }
}

int fcfs(){
    
    int i;
    Processo *p;
    sint size = getLast(manager->tabelaPcb);    
    for(i = 0; i < size; ++i){
        
        if(manager->pidPronto[i] == 1){ // se o processo estiver pronto.
                        
            p = getObj(manager->tabelaPcb, i);                        
            return p->pid;
        }
    } // Se acabar os processos na fila de pronto 
      // tenta retornar um bloqueado ou manter o processo da cpu.
    return retPBloq(size);            
}

int roundRobin(sint posicao){
        
    Processo *p;
    sint size = getLast(manager->tabelaPcb);
    if(posicao == size - 1){
        posicao = 0;
    }   
    for(;posicao < size ; posicao++){
        
        if(manager->pidPronto[posicao] == 1){
            
            p = getObj(manager->tabelaPcb, posicao);
            return p->pid;
        }
    }
    return retPBloq(size);   
}

int definePrioridade(Processo *p){
    
    return p->vetorInst->size;
}

int priStatic(sint base){
    
    int i, pid = -1;
    Processo *p;
    sint size = getLast(manager->tabelaPcb), temp = base;    
    for(i = 0; i < size; ++i){
        
        if(manager->pidPronto[i] == 1){ 
                                                        
            p = getObj(manager->tabelaPcb, i);            
            if(compare(p->prioridade, temp)){
                
                temp = p->prioridade;
                pid = p->pid;
            }            
        }                
    } 
    if(pid > -1){
        
        return pid;
    }
    // Se acabar os processos na fila de pronto 
    // tenta retornar um bloqueado ou manter o processo da cpu.
    return retPBloq(size);            
}
/*
void setPriori(Processo *p, sint v){
    
    p->prioridade = p->prioridade + v;
}
*/
int priDinamic(sint base, sint reajuste){
    
    int i, pid = -1;
    Processo *p;
    sint size = getLast(manager->tabelaPcb), temp = base;    
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

void sendP(Processo *p, sint leg0, sint leg1, sint leg2){
        
    sint size_sint = sizeof(sint);    
    write(1, &manager->tempoGeral, size_sint);
    write(1, &p->pid, size_sint);
    write(1, &p->pidPai, size_sint);
    write(1, &p->prioridade, size_sint);
    write(1, &p->valorInteiro, sizeof (int));
    write(1, &p->tempoInicio, size_sint);
    write(1, &p->tempoAcumulado, size_sint);
    write(1, &leg0, size_sint);
    write(1, &leg1, size_sint);
    write(1, &leg2, size_sint);    
}

void callReporter(){
        
    int pr[2];
    if(pipe(pr)){
        
        printf("Falha ao criar pipe.\n");
        return;
    }
    pid_t pid, fim;
    if((pid = fork()) == 0){// pid do processo filho
        
        close(pr[1]);        
        // alterando stdin do processo filho.
        if(dup2(pr[0], 0) < -1){
            
            return;
        }
        if(execvp("./rpter", (char **) NULL) < 0){
            
            printf("Falha na troca de imagem.\n");
            return;
        }
    }else if(pid < 0){
        
        printf("Falha ao criar fork para process manager...\n");
        return;
    }else{
                     
        int fd_bkp = dup(1);
        
        // alterando stdout do processo pai.
        if (dup2(pr[1], 1) < -1) {

            printf("Erro dup2 processo filho.\n");
            return;
        }
        close(pr[0]); // fechando pipe de leitura.
        // enviando tabela pcb pelo pipe.
            // Enviando o processo atual na CPU                
        Processo *temp = getObj(manager->tabelaPcb, manager->pidExec);                
        temp->valorInteiro = manager->cpu->valorInteiro;        
        sint leg0 = 1, leg1 = 1, leg2 = 1;                     
        sendP(temp, leg0, leg1, leg2);    
        temp = NULL;
        leg0 = 0;
        leg1 = 2;
        leg2 = 1;
        
        int i;        
        for(i = 0; i < getLast(manager->tabelaPcb); ++i){ 
            
            if (manager->pidBloq[i] == 1){
                    
                temp = getObj(manager->tabelaPcb, i);                                
                sendP(temp, leg0, leg1, leg2);                                
                leg2 = 0;                
            }               
        }
        
        temp = NULL;
        leg1 = 3;
        leg2 = 1;
        
        for(i = 0; i < getLast(manager->tabelaPcb); ++i){ 
            
            if (manager->pidPronto[i] == 1) {

                temp = getObj(manager->tabelaPcb, i);
                sendP(temp, leg0, leg1, leg2);                
                leg2 = 0;
            }
        }        
        temp = NULL;        
        
        close(pr[1]);   
        dup2(fd_bkp, 1);
        close(fd_bkp);
        fim = wait(&pid);                 
        if(fim < 0){
            
            printf("ERRO PROCESSO FILHO\n");
        }        
    }   
}

// Funções de impressão e debug.

void showInst(TadInst *t){
    
    int i;
    printf("Qtade de Instruções: %d\n\n", t->size);
    for(i = 0; i < t->size; ++i){
        
        printf("I: %c, Dados: %s\n", t->instrucao[i], t->dados[i]);
    }
    printf("\n");
}