# Makefile para os modulos commander (cmder), process-manager (pmnger) e reporter (rpter).

# Declaração das variáveis de compilação.
CC = gcc
FLAGS = -c -Wall -O3
HDRS = src/headers/
SRC = src/cfiles/
	
# Comando de compilação dos três módulos.
all:	cmder	pmnger	rpter

# Compilação do commander.
cmder:	cmd.o
	$(CC) -o cmder

cmd.o:	$(SRC)cmd.c	commander.o
	$(CC) $(CFLAGS)cmd.c
	
commander.o:	$(HEADERS)commander.h	$(SRC)commander.c
	$(CC) $(CFLAGS)commander.c
	
# Compilação do process manager
pmnger:	pmanager.o
	$(CC) -o pmnger

pmanager.o:	$(SRC)pmanager.c	pm.o
	$(CC) $(CFLAGS)pmanager.c
	
pm.o:	$(HEADERS)pm.h	$(SRC)pm.c
	$(CC) $(CFLAGS)pm.c

# Compilção do reporter.
rpter:	rporter.o
	$(CC) -o rpter
	
rporter.o:	$(SRC)rporter.c	reporter.o
	$(CC) $(CFLAGS)rporter.c
	
reporter.o:	$(HEADERS)reporter.h	pm.o
	$(CC) $(CFLAGS)reporter.c
	
# Limpar objetos de compilação

clean:
	rm -rf *.o
