#ifndef arraylist_H
#define arraylist_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE_INIT 1000 // Define um valor inicial para a quantida de células do arraylist.

typedef struct arraylist {
    
    void *obj; // recebe um vetor de objetos com tamanho size.
    void *first; // mantem salvo o endereço da posição inicial do vetor.
    int last; // mantem salvo a posição.        
    int sizeObj; // recebe o tamanho de uma celula. (serve de base para incremento e 
                // decremento no ponteiro do array.       
    int size;
    short int *dirty; // defini se uma posição do array esta disponível.
}Arraylist;

Arraylist *newArray(short int sizeObj);

void *getObj(Arraylist *array, int id);

void addObj(Arraylist *array, void *obj);

void removeObj(Arraylist *array, int id);

void *myrealloc(void *vetor, size_t len, size_t newLen, size_t sizeType);

#endif