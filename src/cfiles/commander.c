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
        
        printf("Não foi possível abrir o arquivo.\n");
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
        printf("--:> %c\n", ((*cmd)[cont]));
        cont++;       
    }    
    cont++;    
    *cmd = (char *) myrealloc(*cmd, (size_t)size, (size_t)cont, sizeof(char));    
    return cont;
}