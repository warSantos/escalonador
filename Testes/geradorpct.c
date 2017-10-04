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
	
	pont_arq = fopen("procedimentos.txt", "w");
    
    while(counter < linhas)
    {
        randChar = "QUPT"[random () % 4];
        fprintf(pont_arq, "%c\n", randChar);
        counter++;
    } 
    
    fclose(pont_arq);  
    return 0;
}
 
