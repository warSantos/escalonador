#ifndef commander_H
#define commander_H

#include "utils.h"
#include <sys/types.h>
#include <unistd.h>

typedef short int sint;

// Função que le o arquivo de instruções e retorna estas armzenzadas em um vetor.
sint leArquivo(char *fileCmd, char **cmd);

// Envia comandos através do pipe para o Process Manager.
sint enviaComandos(char *vInst, sint size);
#endif