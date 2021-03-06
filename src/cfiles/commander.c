#include "../headers/commander.h"

#define LEN 10000 // define a quantidade inicial de 
                  // memmória em bytes a ser alocada para o vetor de instruções.

int leArquivo(char *fileCmd, char **cmd){

    FILE *leitor = fopen(fileCmd, "r");
    if(leitor == NULL){

        return -1;
    }    
    int cont = 0, size = LEN;
    *cmd = malloc(sizeof(char)*size);
    
    while(fscanf(leitor, "%c\n", &(*cmd)[cont]) != EOF){
    
        if(cont == size - 2){ // hora de allocar mais memória para o vetor.
            
            // Dobrando a quantidade de memória para o novo vetor
            *cmd = (char *) myrealloc((void *)*cmd, size, size * 2, sizeof(char));            
            size *= 2;            
        }                        
        cont++;       
        
    }    
    *cmd = (char *) myrealloc(*cmd, (size_t)size, (size_t)cont, sizeof(char));                      
    return cont;        
}

int enviaComandos(char *vInst, int size, char **init){
    
    // Criando pipe de comunicação entre o process manager e commander.
    
    int cp[2]; // Vetor com ids de leitura e escrita. Pipe commander -> manager
    if(pipe(cp) < 0){
        
        printf("Falha ao criar pipe.\n");
        return -1;
    }    
    pid_t pid, fim;            
    if((pid = fork()) == 0){ // pid do processo filho.
                
        if(dup2(cp[0], 0) < -1){
            
            printf("Erro dup2 processo filho.\n");
            return -1;
        }
        // Troca de imagem (criando o process Manager).
        if(execvp("./pmnger", init) < 0){
            
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
        int idInst = 0;
        close(cp[0]);
        
        while (idInst < size) { // Enquanto houver instruções...
            
            sleep(1); 
            write(1, &vInst[idInst], 1);            
            idInst++;                           
        }                
        if(idInst == size){
            
            printf("Fim das instruções.\n");
        }
        close(cp[1]);                   
        fim = wait(&pid);                        
        if(fim < 0){
            
            exit(1);
        }
        exit(0);               
    }    
    return -1;
}
