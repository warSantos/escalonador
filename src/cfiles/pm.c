#include "../headers/pm.h"
#include <unistd.h>

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
    temp->pidPai = pidPai;
    temp->prioridade = prioridade;
    temp->tempoInicio = tempoInicio;
    temp->tempoAcumulado = 0;
    temp->vetorInst = criaVetorInst(arquivo);
    if(temp->vetorInst == NULL){
        
        printf("Arquivo de processo não encontrado.\n");
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
    
    printf("\n\npid: %d\n", p->pid);
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

void block(sint *bloq, int pid){
    
    bloq[pid] = 1;
}

void executaProcesso(Cpu *cpu) {       
    
    Processo *temp = getObj(manager->tabelaPcb, manager->pidExec);
    int size = temp->vetorInst->size;
    cpu->tempoCorrente++;
    while (cpu->pInst < size){
               
        switch (cpu->vetorInst->instrucao[cpu->pInst]){//saber qual função sera executada
            case 'S'://valor inteiro é alterado
                
                cpu->valorInteiro = atoi(cpu->vetorInst->dados[0]);
                break;
            case 'A'://soma o valor inteiro com a entrada
                
                cpu->valorInteiro = cpu->valorInteiro + atoi(cpu->vetorInst->dados[0]);
                break;
            case 'D'://subtrai o valor inteiro com a entrada
                
                cpu->valorInteiro = cpu->valorInteiro - atoi(cpu->vetorInst->dados[0]);
                break;
            case 'B'://bloqueia o processo voltando para o escalonador
                
                return;
            case 'E'://termina o processo simulado
            case 'F'://cria processo filho

            case 'R'://abre um arquivo com nome passado e altera o valor inteiro para a primeira instrução do novo processo

            default:
                printf("este comando não existe\n");
        }
        
        cpu->pInst++;
    }
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
    if((pid = fork()) == 0){ // pid do processo filho
        
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
        
        leg0 = 0;
        leg1 = 2;
        leg2 = 1;
        int i;
        for(i = 0; i < manager->tabelaPcb->qtdeObj; ++i){ 
            
            if (manager->pidPronto[i]) {

                temp = getObj(manager->tabelaPcb, i);
                sendP(temp, leg0, leg1, leg2);
                leg2 = 0;
            }
        }
        leg1 = 3;
        leg2 = 1;
        for(i = 0; i < manager->tabelaPcb->qtdeObj; ++i){ 
            
            if (manager->pidBloq[i]) {

                temp = getObj(manager->tabelaPcb, i);
                sendP(temp, leg0, leg1, leg2);
                leg2 = 0;
            }
        }
        close(pr[1]);   
        fim = wait(&pid);                     
    }   
}
