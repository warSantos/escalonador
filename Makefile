CC = gcc
FLAGS = -c -Wall -O3
HDRS = src/headers/
SRC = src/cfiles/
FILES = $(wildcard src/cfiles/*)
OBJ = $(FILES:. c=*.o)
