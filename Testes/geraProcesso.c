#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(){

	srandom(time(NULL));
    char randChar;
	int  linhas, counter = 0, qtdeP, va, bkp;
	FILE *pont_arq; 
	
    printf("Digite quantidade limite de Processos: ");
    scanf("%d", &qtdeP);
    printf("Digite quantidade limite de instruções: ");
    scanf("%d", &linhas);

	linhas=linhas-1;
	bkp = qtdeP;
    char *arq = malloc(sizeof(char)*25);
	while(qtdeP){
	    
	    sprintf(arq ,"%d.txt", qtdeP);
	    pont_arq = fopen(arq, "w");
	    int l = linhas - random () % linhas;
        while(counter < l){
                        
            randChar = "AFDFS"[random () % 5];
            if(randChar == 'A' || randChar == 'D' || randChar == 'S'){
                
                va = random() % 1000;
                fprintf(pont_arq, "%c %d\n", randChar, va);
            }else{
                
                fprintf(pont_arq, "%c 1\n", randChar);
                fprintf(pont_arq, "R %d.txt\n", (qtdeP + 1 + (random() % (bkp - (qtdeP - 1)))));
            }
            counter++;
        }
        counter = 0;
        fprintf(pont_arq, "E\n");
        fclose(pont_arq);
        qtdeP--;
    }    
    free(arq);
    return 0;
}
 