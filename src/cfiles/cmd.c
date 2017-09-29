/*
*  Arquivo 'main' para o modulo commander
*/

#include "../headers/commander.h"

int main(int argc, char **argv){
    
    char *vInst;
    sint size = leArquivo(argv[1], &vInst);
    printf("size %d\n", size);
    sint i;
    for(i = 0; vInst[i] != '\0'; ++i){
        
        printf("%c\n", vInst[i]);
    }
    return 0;
}

/*
 sint i;
    for(i = 0;vInst[i] != '\0'; ++i){
        
        printf("%c\n", vInst[i]);
    }
 */