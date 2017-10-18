#include "../headers/pm.h"
#include <unistd.h>

void debug(){
    
    FILE *e = fopen("syslog.txt","a");
    fprintf(e, "GET HERE!!!\n");
    fclose(e);
}

TadInst *iniciaTadInst(sint size){
            
    TadInst *temp = malloc(sizeof(TadInst));
    temp->instrucao = malloc(sizeof(char) * size);
    temp->dados = malloc(sizeof(char *) * size);    
    temp->size = size;
    return temp;
}

void showInst(TadInst *t){
    
    int i;
    printf("Qtade de Instruções: %d\n\n", t->size);
    for(i = 0; i < t->size; ++i){
        
        printf("I: %c, Dados: %s\n", t->instrucao[i], t->dados[i]);
    }
    printf("\n");
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
    temp->prioridade = prioridade;
    temp->tempoInicio = tempoInicio;
    temp->tempoAcumulado = 0;
    temp->vetorInst = criaVetorInst(arquivo);
    if(temp->vetorInst == NULL){
        
        printf("Arquivo %s de processo não encontrado.\n", arquivo);
        return NULL;
    }    
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

void showP(Processo *p){
    
    printf("\npid: %d\n", p->pid);
    printf("pid do pai: %d\n", p->pidPai);
    printf("instrucão atual: %d\n", p->pc);    
    printf("variável: %d\n", p->valorInteiro);
    printf("prioridade: %d\n", p->prioridade);
    printf("tempo Inicial: %d\n", p->tempoInicio);
    printf("tempo Acumulado: %d\n\n", p->tempoAcumulado);    
    showInst(p->vetorInst);
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
            //printf("Fim\n");
            //showInst(temp);
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

void unblock(sint *bloq, sint *pronto, int size){
    
    int i = 0;
    while(!bloq[i] && i < size){
        
        ++i;
    }
    bloq[i] = 0; // desbloqueando o processo.
    pronto[i] = 1; // movendo ele para fila de pronto.
}

void block(sint *bloq, sint pid){
    
    bloq[pid] = 1;
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
    if(interrupt){
        // verifica se o processo foi bloqueado por uma interrupção.
        manager->pidBloq[manager->pidExec] = 1;
        manager->pidPronto[manager->pidExec] = 0;
    }
    if(manager->pidPronto[manager->pidExec] != -1){
        
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
    //printf("cputempolim: %d\n", cpu->tempoLimite);
    while(cpu->tempoCorrente < cpu->tempoLimite && cpu->pc < temp->vetorInst->size){
               
        switch (cpu->vetorInst->instrucao[cpu->pc]){//saber qual função sera executada
            case 'S'://valor inteiro é alterado
                
                cpu->valorInteiro = atoi(cpu->vetorInst->dados[0]);
                break;
            case 'A'://soma o valor inteiro com a entrada
                
                cpu->valorInteiro += atoi(cpu->vetorInst->dados[0]);
                break;
            case 'D'://subtrai o valor inteiro com a entrada
                
                cpu->valorInteiro -= atoi(cpu->vetorInst->dados[0]);
                break;
            case 'B'://bloqueia o processo voltando para o escalonador
                // aqui tbm deve ser chamada a função de troca de contexto.
                block(manager->pidBloq, manager->pidExec);
                // chama função ou funções de heurística de escalonamento.
                //trocaContexto( , , 1);
                return;
            case 'E'://termina o processo simulado
                
                printf("\nTerminou processo %d.\n\n", temp->pid);
                manager->pidPronto[temp->pid] = -1;
                int h;
                for(h = 0; h < getLast(manager->tabelaPcb); ++h){
            
                    printf("Pid: %d, Pronto: %d\n", h, manager->pidPronto[h]);
                }
                break;
            case 'F'://cria processo filho
                break;  
            case 'R'://abre um arquivo com nome passado e altera o valor inteiro para a primeira instrução do novo processo                                
                
                id = 0;
                while(manager->pidPronto[id] != -1 && id < getLast(manager->tabelaPcb)){
                    
                    ++id;
                }
                
                printf("ID: %d\n", id);
                fk = newProcesso(id, temp->pid, 15, manager->tempoGeral,
                        temp->vetorInst->dados[cpu->pc]);
                if(id < getLast(manager->tabelaPcb)){
                
                    changeObj(manager->tabelaPcb, (void *)fk, id);
                }else{
                    
                    int bkp_size = getSize(manager->tabelaPcb);
                    if (addObj((void *) manager->tabelaPcb, (void *) fk)) {

                        manager->pidBloq = myrealloc(manager->pidBloq, bkp_size, getSize(manager->tabelaPcb), sizeof (sint));
                        manager->pidPronto = myrealloc(manager->pidPronto, bkp_size, getSize(manager->tabelaPcb), sizeof (sint));
                    }     
                }
                manager->pidPronto[fk->pid] = 1;
                break;
            default:
                printf("Comando inválido %c.\n", cpu->vetorInst->instrucao[cpu->pc]);
        }
        cpu->pc++;
        cpu->tempoCorrente++;        
    }            
}
/*
int k;
        Processo *p;
        for (k = 0; k < getLast(manager->tabelaPcb); ++k) {

            p = getObj(manager->tabelaPcb, k);
            showP(p);
        }
        printf("**************************************************************************************\n");
        printf("**************************************************************************************\n");
        system("pause\n");
        //printf("pid: %d pc %d tmc %d\n", temp->pid, cpu->pc, cpu->tempoCorrente);
        //printf("intrucao: %c, dados %s\n", cpu->vetorInst->instrucao[cpu->pc], cpu->vetorInst->dados[cpu->pc]);                          
                  
*/
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
        
        // alterando stdout do processo pai.
        if (dup2(pr[1], 1) < -1) {

            printf("Erro dup2 processo filho.\n");
            return;
        }
        close(pr[0]); // fechando pipe de leitura.
        // enviando tabela pcb pelo pipe.
            // Enviando o processo atual na CPU                
        Processo *temp = getObj(manager->tabelaPcb, 0);                
        temp->valorInteiro = manager->cpu->valorInteiro;        
        sint leg0 = 1, leg1 = 1, leg2 = 1;     
        
        //showP(temp);        
        sendP(temp, leg0, leg1, leg2);    
        temp = NULL;
        leg0 = 0;
        leg1 = 2;
        leg2 = 1;
        int i;
        
        for(i = 0; i < 10/*getSize(manager->tabelaPcb)*/; ++i){ 
            
            if (manager->pidPronto[i]) {
                    
                temp = getObj(manager->tabelaPcb, i);                
                sendP(temp, leg0, leg1, leg2);
                //showP(temp);        
                leg2 = 0;
            }            
        }
        temp = NULL;
        leg1 = 3;
        leg2 = 1;
        for(i = 0; i < 10/*getSize(manager->tabelaPcb)*/; ++i){ 
            
            if (manager->pidBloq[i]) {

                temp = getObj(manager->tabelaPcb, i);
                sendP(temp, leg0, leg1, leg2);
                leg2 = 0;
            }
        }
        temp = NULL;
        
        close(pr[1]);   
        
        
        fim = wait(&pid);                 
        if(fim < 0){
            
            printf("ERRO PROCESSO FILHO\n");
        }        
    }   
}

void showP2(Processo *p){
    
    FILE *e = fopen("process.log", "a");
    
    fprintf(e, "\npid: %d\n", p->pid);
    fprintf(e, "pid do pai: %d\n", p->pidPai);
    fprintf(e, "instrucão atual: %d\n", p->pc);        
    fprintf(e, "prioridade: %d\n", p->prioridade);
    fprintf(e, "variável: %d\n", p->valorInteiro);/*
    printf("tempo Inicial: %d\n", p->tempoInicio);
    printf("tempo Acumulado: %d\n\n", p->tempoAcumulado);    
    showInst(p->vetorInst);*/
    fclose(e);
}

int fcfs(){
    
    int i;
    Processo *p;
    sint size = getLast(manager->tabelaPcb);
    printf("\ngetLast: %d\n", size);
    for(i = 0; i < size; ++i){
        
        if(manager->pidPronto[i] == 1){ // se o processo estiver pronto.
            
            p = getObj(manager->tabelaPcb, i);
            return p->pid;
        }
    }
    for(i = 0; i < size; ++i){
        
        if(manager->pidBloq[i] == 1){ // se o processo estiver bloqueado
            
            p = getObj(manager->tabelaPcb, i);
            unblock();
            return p->pid;
        }
    }
    return -1; // se ele nao achar nenhuem processo pronto ele retorna -1.
}