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
    return temp;
}

TadPm *iniciaPM(){

    TadPm *temp = malloc(sizeof(TadPm));
    temp->tempoGeral = 0;    
    temp->pidExec = 0;
    temp->cpu = iniciaCpu();      
    temp->tabelaPcb = newArray(sizeof(Processo));
    temp->pidPronto = calloc(sizeof(sint), getSize(tabelaPcb));
    temp->pidBloq = calloc(sizeof(sint), getSize(tabelaPcb));
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
            printf("Fim\n");
            showInst(temp);
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

void callReporter(){
    
    int pr[2];
    if(pipe(pr)){
        
        printf("Falha ao criar pipe.\n");
        return;
    }
    pid_t pid /*, fim*/;
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
        Processo *temp = getObj(manager->tabelaPcb, manager->pidExec);
        // Enviando o processo atual na CPU
        sint size_sint = sizeof(sint), leg0 = 1, leg1 = 1;
        sint estado = 0; // bloqueado 2, executando 0, pronto 1.
        write(1, &temp->pid, size_sint);
        write(1, &temp->pidPai, size_sint);
        write(1, &temp->prioridade, size_sint);
        write(1, &manager->cpu->valorInteiro, sizeof(int));
        write(1, &temp->tempoAcumulado, size_sint);
        write(1, &estado, size_sint);
        write(1, &leg0, size_sint);
        write(1, &leg1, size_sint);
        
        leg0 = 0;
        leg1 = 2;
        int i;
        for(i = 0; i < manager->tabelaPcb->qtdeObj; ++i){ 
            
            if (manager->pidPronto[i]) {

                temp = getObj(manager->tabelaPcb, i);
                write(1, &temp->pid, size_sint);
                write(1, &temp->pidPai, size_sint);
                write(1, &temp->prioridade, size_sint);
                write(1, &temp->valorInteiro, sizeof (int));
                write(1, &temp->tempoAcumulado, size_sint);
                write(1, &estado, size_sint);
                write(1, &leg0, size_sint);
                write(1, &leg1, size_sint);
            }
        }
        leg1 = 3;
        for(i = 0; i < manager->tabelaPcb->qtdeObj; ++i){ 
            
            if (manager->pidBloq[i]) {

                temp = getObj(manager->tabelaPcb, i);
                write(1, &temp->pid, size_sint);
                write(1, &temp->pidPai, size_sint);
                write(1, &temp->prioridade, size_sint);
                write(1, &temp->valorInteiro, sizeof (int));
                write(1, &temp->tempoAcumulado, size_sint);
                write(1, &estado, size_sint);
                write(1, &leg0, size_sint);
                write(1, &leg1, size_sint);
            }
        }
        close(pr[1]);   
        //fim = wait(pid);                
    }
}
void Executaprocesso(Cpu *cpu){
    sint tempo = 0;
    cpu->tempoInicio = //nao faço ideia como fazer esta bosta;
    while(cpu->pInst < cpu->size){
        tempo++;
        switch(cpu->vetorInst[cpu->pInst].instrucao){//saber qual função sera executada
            case 'S'://valor inteiro é alterado
                cpu->tempoCorrente= cpu->tempoCorrente + 1;
                cpu->valorInteiro = atoi(&cpu->vetorInst[cpu->pInst].dados);
                break;
            case 'A'://soma o valor inteiro com a entrada
                cpu->tempoCorrente= cpu->tempoCorrente + 1;
                cpu->valorInteiro = cpu->valorInteiro + atoi(&cpu->vetorInst[cpu->pInst].dados);
                break;
            case 'D'://subtrai o valor inteiro com a entrada
                cpu->tempoCorrente= cpu->tempoCorrente + 1;
                cpu->valorInteiro = cpu->valorInteiro - atoi(&cpu->vetorInst[cpu->pInst].dados);
                break;
            case 'B'://bloqueia o processo voltando para o escalonador
                cpu->tempoCorrente= cpu->tempoCorrente + 1;
                return;
            case 'E'://termina o processo simulado
            case 'F'://cria processo filho
                
            case 'R'://abre um arquivo com nome passado e altera o valor inteiro para a primeira instrução do novo processo

            default:
                printf("este comando não existe\n");
        }
    }
}