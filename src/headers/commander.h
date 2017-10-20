#ifndef commander_H
#define commander_H

#include "utils.h"
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

// Função que le o arquivo de instruções e retorna estas armzenzadas em um vetor.
int leArquivo(char *fileCmd, char **cmd);

// Envia comandos através do pipe para o Process Manager.
int enviaComandos(char *vInst, int size, char **init);
#endif