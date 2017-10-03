/*
*  Arquivo 'main' para o modulo pmanager
*/

#include "../headers/pm.h"

int main(int argc, char **argv){
    
    
    int setPipe[2];
    printf("argc %d\n", argc);
    printf("%s %s %s\n", argv[0], argv[1], argv[2]);
    
    memcpy((void *)&setPipe[0], (void *)argv[0], sizeof(char)*4);
    memcpy((void *)&setPipe[1], (void *)argv[1], sizeof(char)*4);
    printf("%d %d %d\n\n\n", argc, setPipe[0], setPipe[1]);
    printf("Execvp iniciado.\n");
    return 0;
}