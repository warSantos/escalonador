#include "../headers/commander.h"

#define N 10000

sint leArquivo(char *fileCmd, char **cmd){

    FILE *leitor = fopen(fileCmd, "r");
    if(leitor == NULL){

        return -1;
    }    
    sint cont = 0, size = N;
    *cmd = malloc(sizeof(char)*size);
    while(fscanf(leitor, "%c\n", &(*cmd)[cont]) != EOF){
    
        if(cont == size - 2){ // hora de allocar mais memória para o vetor.
            
            // Dobrando a quantidade de memória para o novo vetor
            *cmd = (char *) myrealloc(cmd, size, size * 2, sizeof(char));
            size *= 2;            
        }                        
        cont++;       
    }        
    *cmd = (char *) myrealloc(*cmd, (size_t)size, (size_t)cont, sizeof(char));        
    return cont;
}

sint enviaComandos(char *vInst, sint size){
    
    // Criando pipe de comunicação entre o process manager e commander.
    
    int cp[2]; // Vetor com ids de leitura e escrita. Pipe commander -> manager
    if(pipe(cp) < 0){
        
        printf("Falha ao criar pipe.\n");
        return -1;
    }
    /*    
    int h;
    for(h = 0; h < size;++h){
        
        //printf("h: %d %c\n", h, vInst[h]);
    }*/
    pid_t pid /*, fim*/;            
    if((pid = fork()) == 0){ // pid do processo filho.
                
        if(dup2(cp[0], 0) < -1){
            
            printf("Erro dup2 processo filho.\n");
            return -1;
        }
        // Troca de imagem (criando o process Manager).
        if(execvp("./pmnger", (char **)NULL) < 0){
            
            printf("Falha na troca de imagem.\n");
            return -1;
        }        
    }else if(pid < 0){ // erro ao criar fork.
                
        printf("Falha ao criar fork para process manager...\n");
        return -1;
    }else{ // pid do processo pai       
        
        if (dup2(cp[1], 1) < -1) {

            printf("Erro dup2 processo filho.\n");
            return -1;
        }              
        sint idInst = 0;
        close(cp[0]);
        
        while (idInst < size) { // Enquanto houver instruções...
            
            //sleep(1);            
            write(1, &vInst[idInst], 1);            
            idInst++;            
        }  
        close(cp[1]);   
        //fim = wait(pid);        
        exit(0);
    }
    return -1;
}
