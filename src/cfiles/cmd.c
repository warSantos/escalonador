/*
*  Arquivo 'main' para o modulo commander
*/

#include "../headers/commander.h"

int main(int argc, char **argv){
    
    char *vInst;
    int size;
    if((size = leArquivo(argv[1], &vInst)) == -1){
        
        printf("Não foi possível abrir o arquivo.\n");
        return 1;
    }    
    enviaComandos(vInst, size, argv);
    return 0;
}
