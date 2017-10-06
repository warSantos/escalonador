/*
*  Arquivo 'main' para o modulo commander
*/

#include "../headers/commander.h"

int main(int argc, char **argv){
    
    char *vInst;
    sint size;
    if((size = leArquivo(argv[1], &vInst)) == -1){
        
        printf("Não foi possível abrir o arquivo.\n");
        return 1;
    }  
    printf("size %d\n", size);
    enviaComandos(vInst, size);
    return 0;
}

/*
 sint i;
    for(i = 0;vInst[i] != '\0'; ++i){
        
        printf("%c\n", vInst[i]);
    }
 */