# Makefile para os modulos commander (cmder), process-manager (pmnger) e reporter (rpter).

# Declaração das variáveis de compilação.
CC = gcc
CFLAGS = -c -Wall -O3
HDRS = src/headers/
SRC = src/cfiles/
	
# Comando de compilação dos três módulos.
all:	cmder	pmnger	rpter

# Compilação do commander.
cmder:	cmd.o	commander.o 
	$(CC) cmd.o commander.o -o cmder

cmd.o:	$(SRC)cmd.c
	$(CC) $(CFLAGS)	$(SRC)cmd.c
	
commander.o:	$(HDRS)commander.h	$(SRC)commander.c
	$(CC) $(CFLAGS) $(SRC)commander.c
	
# Compilação do process manager
pmnger:	pmanager.o	pm.o
	$(CC) pmanager.o pm.o -o pmnger

pmanager.o:	$(SRC)pmanager.c
	$(CC) $(CFLAGS) $(SRC)pmanager.c
	
pm.o:	$(HDRS)pm.h	$(SRC)pm.c
	$(CC) $(CFLAGS) $(SRC)pm.c

# Compilção do reporter.
rpter:	rporter.o	reporter.o
	$(CC) rporter.o reporter.o -o rpter
	
rporter.o:	$(SRC)rporter.c
	$(CC) $(CFLAGS) $(SRC)rporter.c
	
reporter.o:	$(HDRS)reporter.h
	$(CC) $(CFLAGS) $(SRC)reporter.c
	
# Limpar objetos de compilação

clean:
	rm -rf *.o
