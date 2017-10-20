#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
	srandom(time(NULL));  
    char randChar;
	int  linhas, counter = 0;
	FILE *pont_arq; 
	
    printf("Digite quantidade de comandos \n");
    scanf("%d", &linhas);
	
	pont_arq = fopen("cmds.txt", "w");
    
    while(counter < linhas){
    
        randChar = "QQQ"[random () % 3];
        fprintf(pont_arq, "%c\n", randChar);
        counter++;
    } 
    fprintf(pont_arq, "T\n");
    fclose(pont_arq);  
    return 0;
}
