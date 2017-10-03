#include "../headers/commander.h"

#define N 10000
#define ate printf("Ate aqui foi\n");

void *myrealloc(void *vetor, size_t len, size_t newLen, size_t sizeType){
        
    if(len < 0 || newLen < 0){
        
        return NULL;
    }
    char *temp = (char *) vetor;        
    int i, endVet;
    if(newLen < len){
        
        endVet = sizeType * newLen;
    }else{
        
        endVet = sizeType * len;        
    }
    char *newVet = malloc(sizeType * newLen);    
    for(i = 0; i < endVet; ++i){
                  
        newVet[i] = temp[i];        
    }    
    free(temp);
    return (void *) newVet;
}

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
    cont++;    
    *cmd = (char *) myrealloc(*cmd, (size_t)size, (size_t)cont, sizeof(char));    
    return cont;
}

sint enviaComandos(char *vInst, sint size){
    
    // Criando pipe de comunicação entre o process manager e commander.
    int setPipe[2]; // Vetor com ids de leitura e escrita.
    if(pipe(setPipe) < 0){
        
        printf("Falha ao criar pipe.\n");
        return -1;
    }
    printf("pipes %d %d\n", setPipe[0], setPipe[1]);
    // alterando vetor de int para vetor de char.
    char *idPipeR = malloc(sizeof(char)*4);
    char *idPipeW = malloc(sizeof(char)*4);    
    memcpy(idPipeR, &setPipe[0], sizeof(int));
    memcpy(idPipeW, &setPipe[1], sizeof(int));
    
    printf("atoi %d\n", atoi(idPipeW));
    // Criando fork para o Processo manager...
    pid_t pidPM;
    if((pidPM = fork()) == 0){
        // Falta terminar a troca de imagem.
        printf("Codigo do filho.\n");
        if(execlp("./pmnger","./pmnger", (char *)NULL) < 0){
            
            printf("Falha na troca de imagem.\n");
            return -1;
        }
        
    }else if((pidPM = fork()) < 0){
                
        printf("Falha ao criar fork para process manager...\n");
        return -1;
    }else{
        
        printf("Codigo do pai.\n");
    }
    
    /*
    sint idInst = 0;
    while(idInst < size){ // Enquanto houver instruções...
        
        idInst++;
    }
    */
    return -1;
}