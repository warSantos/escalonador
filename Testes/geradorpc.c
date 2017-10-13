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
	linhas=linhas-1;
	
	pont_arq = fopen("procedimentos.txt", "w");
    
    while(counter < linhas)
    {
        randChar = "QUP"[random () % 3];
        fprintf(pont_arq, "%c\n", randChar);
        counter++;
    } 
    fprintf(pont_arq, "T\n");
    fclose(pont_arq);  
    return 0;
}
 
