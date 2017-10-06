/*
*  Arquivo 'main' para o modulo pmanager
*/

#include "../headers/pm.h"

int main(int argc, char **argv){
        
    char inst;
    while(read(0, &inst, 1)){
        
        printf("inst: %c\n", inst);        
    }
    return 0;
}