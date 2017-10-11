/*
 Biblioteca com funções suporte extras.
 */

#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// cria um vetor novo e copia os dados do antigo para o novo.
void *myrealloc(void *vetor, size_t len, size_t newLen, size_t sizeType);

#endif /* UTILS_H */

