#include "../headers/arraylist.h"

Arraylist *newArray(short int sizeObj){
    
    Arraylist *temp = malloc(sizeof(Arraylist));
    temp->sizeObj = sizeObj; // armazenando o tamamho de um Obj.
    temp->obj = malloc(SIZE_INIT * (sizeObj)); // atribuição do vetor de objetos
    temp->first = temp->obj; // inicializando o apontador para inicio da fila.                        
    temp->last = 0;
    temp->size = SIZE_INIT; // quantidade inicial de memória alocada.
    temp->dirty = calloc(sizeof(short int), SIZE_INIT);
    return temp;
}

void *getObj(Arraylist *array, int id){
    
    while(array->dirty[id]){
        
        id++;
    }
    return array->obj + (id * array->sizeObj);
}

void addObj(Arraylist *array, void *obj){
        
    if(array->last == array->size){// se o limite do vetor foi atingido.
                        
        array->obj = myrealloc(array->obj, array->size, array->size + SIZE_INIT, array->sizeObj);
        array->dirty = myrealloc(array->dirty, array->size, array->size + SIZE_INIT, sizeof(short int));
        array->first = array->obj;
        array->size = array->size + SIZE_INIT;        
    }
    array->last += array->sizeObj;
    
    memcpy(array->obj + (array->last*array->sizeObj), obj, array->sizeObj); // copiando o objeto para o array de objetos;            
}

void removeObj(Arraylist *array, int id){
    
    array->dirty[id] = 1; //marcando o objeto como "deletado". 
}

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