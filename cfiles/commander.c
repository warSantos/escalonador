#include "../headers/commander.h"

#define N 10000

void *myrealloc(void *vetor, size_t len, size_t newLen, size_t sizeType){
    
    char *temp = (char *) vetor;    
    int i, endVet = sizeType * len;
    char *newVet = malloc(sizeType * newLen); //*temp2 = newVet;    
    for(i = 0; i < endVet; ++i){
          
        //*newVet++ = *temp++; 
        newVet[i] = temp[i];
    }
    free(temp);
    return (void *) newVet;
}

char *leArquivo(char *fileCmd){
    
    FILE *leitor = fopen(fileCmd, "r");
    if(leitor == NULL){
        
        printf("Não foi possível abrir o arquivo.\n");
        return;
    }
    sint cont = 0, size = N;
    char *cmd = malloc(sizeof(char)*N);
    while(fscanf(leitor, "%c", cmd[cont])!=EOF){
    
        if(cont == size - 2){ // hora de allocar mais memória para o vetor.
            
            // Dobrando a quantidade de memória para o novo vetor
            cmd = (char *) myrealloc(cmd, size, size * 2, sizeof(char));
            size *= 2;
        }                
        cont++;        
    }
    cmd[cont++] = '\0';
    return cmd;
}