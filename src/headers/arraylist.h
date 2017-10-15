#ifndef arraylist_H
#define arraylist_H

#include "utils.h"

#define SIZE_INIT 1000 // Define um valor inicial para a quantida de células do arraylist.

typedef struct arraylist {
    
    void *obj; // recebe um vetor de objetos com tamanho size.
    void *first; // mantem salvo o endereço da posição inicial do vetor.
    int last; // mantem salvo a posição.        
    int sizeObj; // recebe o tamanho de uma celula. (serve de base para incremento e 
                // decremento no ponteiro do array.       
    int size; // quantidade de posisões alocadas no vetor.
    int qtdeObj; // quantidade de objetos válidos no vetor.    
}Arraylist;


// Cria um novo arraylist genérico.
Arraylist *newArray(short int sizeObj);

// Altera a um objeto do array através do id.
void changeObj(Arraylist *array, void *obj, int id);

// Retorna o endereço de um objeto.
void *getObj(Arraylist *array, int id);

// Adiciona um objeto ao final do arraylist.
short int addObj(Arraylist *array, void *obj);

// cria um vetor novo e copia os dados do antigo para o novo.
void *myrealloc(void *vetor, size_t len, size_t newLen, size_t sizeType);

#endif
