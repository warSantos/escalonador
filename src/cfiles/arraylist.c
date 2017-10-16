#include "../headers/arraylist.h"

Arraylist *newArray(short int sizeObj){
    
    Arraylist *temp = malloc(sizeof(Arraylist));
    temp->sizeObj = sizeObj; // armazenando o tamamho de um Obj.
    temp->obj = malloc(SIZE_INIT * (sizeObj)); // atribuição do vetor de objetos
    temp->first = temp->obj; // inicializando o apontador para inicio da fila.                        
    temp->last = 0;
    temp->size = SIZE_INIT; // quantidade inicial de memória alocada.    
    temp->qtdeObj = 0;
    return temp;
}

void *getObj(Arraylist *array, int id){
        
    return array->obj + (id * array->sizeObj);
}

int getLast(Arraylist *array){
    
    return (array->last / array->sizeObj);
}

int getSize(Arraylist *array){
    
    return array->size;
}

int getQtdObj(Arraylist *array){
        
    return array->qtdeObj;
}

void changeObj(Arraylist *array, void *obj, int id){
    
    memcpy(array->obj + (id * array->sizeObj), obj, array->sizeObj);
}

short int addObj(Arraylist *array, void *obj){
    
    short int flag = 0;
    if((array->last / array->sizeObj) == array->size){// se o limite do vetor foi atingido.
                      
        array->obj = myrealloc(array->obj, array->size, array->size + SIZE_INIT, array->sizeObj);        
        array->first = array->obj;
        array->size = array->size + SIZE_INIT;        
        flag = 1;
    }
    memcpy(array->obj + array->last, obj, array->sizeObj); // copiando o objeto para o array de objetos;            
    array->last += array->sizeObj;
    array->qtdeObj++;
    return flag;
}
