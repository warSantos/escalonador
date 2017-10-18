# Makefile para os modulos commander (cmder), process-manager (pmnger) e reporter (rpter).

# Declaração das variáveis de compilação.
CC = gcc
CFLAGS = -c -Wall -O3
HDRS = src/headers/
SRC = src/cfiles/
OBJ = ./obj/
MKD = mkdir -p obj	

# Comando de compilação dos três módulos.
all:	cmder	pmnger	rpter

# Compilação do commander.
cmder:	cmd.o	commander.o	utils.o
	$(CC) $(OBJ)cmd.o $(OBJ)commander.o $(OBJ)utils.o -o cmder

cmd.o:	mk	$(SRC)cmd.c
	$(CC) $(CFLAGS) $(SRC)cmd.c -o $(OBJ)cmd.o
	
commander.o: mk	$(HDRS)commander.h	$(SRC)commander.c
	$(CC) $(CFLAGS) $(SRC)commander.c -o $(OBJ)commander.o
	
# Compilação do process manager
pmnger:	pmanager.o	pm.o	utils.o
	$(CC) $(OBJ)pmanager.o $(OBJ)pm.o $(OBJ)arraylist.o $(OBJ)utils.o -o pmnger

pmanager.o:	mk	$(SRC)pmanager.c
	$(CC) $(CFLAGS) $(SRC)pmanager.c -o $(OBJ)pmanager.o
	
pm.o:	mk	arraylist.o	$(HDRS)pm.h	$(SRC)pm.c
	$(CC) $(CFLAGS) $(SRC)pm.c -o $(OBJ)pm.o

# Compilção do reporter.
rpter:	mk  pm.o    rporter.o	reporter.o
	$(CC) $(OBJ)pm.o $(OBJ)arraylist.o $(OBJ)utils.o $(OBJ)rporter.o $(OBJ)reporter.o -o rpter
	
rporter.o:	mk	$(SRC)rporter.c
	$(CC) $(CFLAGS) $(SRC)rporter.c -o $(OBJ)rporter.o
	
reporter.o:	mk	$(HDRS)reporter.h
	$(CC) $(CFLAGS) $(SRC)reporter.c -o $(OBJ)reporter.o

# Compilação do Arraylist

arraylist.o:	mk	$(HDRS)arraylist.h	$(SRC)arraylist.c
	$(CC) $(CFLAGS) $(SRC)arraylist.c -o $(OBJ)arraylist.o

# Compilação do utils

utils.o:	mk	$(HDRS)utils.h	$(SRC)utils.c
	$(CC) $(CFLAGS) $(SRC)utils.c -o $(OBJ)utils.o
	
mk:
	$(MKD)

# Limpar objetos de compilação

clean:
	rm -rf $(OBJ)*.o

del:
	rm pmnger cmder rpter
# Executar

run:
	rm -f syslog.txt process.log && make all && ./cmder teste && ls
