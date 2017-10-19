#include "../headers/utils.h"

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


void debug(){
    
    FILE *e = fopen("syslog.txt","a");
    fprintf(e, "GET HERE!!!\n");
    fclose(e);
}