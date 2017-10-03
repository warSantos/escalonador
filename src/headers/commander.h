#ifndef commander_H
#define commander_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

typedef short int sint;

// Realiza realocação de memória para vetor.
void *myrealloc(void *vetor, size_t len, size_t newLen, size_t sizeType);

// Função que le o arquivo de instruções e retorna estas armzenzadas em um vetor.
sint leArquivo(char *fileCmd, char **cmd);

// Envia comandos através do pipe para o Process Manager.
sint enviaComandos(char *vInst, sint size);
#endif