#Se definen los objetos , estos son los archivos que necesitan
#para crear el ejecutable .

OBJS_DOC = doc.cnf
OBJS_CPP1 = class_cache_multinivel.cpp
MAIN = main.cpp
#MAIN2 = main2.cpp
HEADER1 = class_cache_multinivel.h
OUT1 = class_cache.o
TARGET = ejecutable
#TARGET2 = ejecutable2
#Se define e l compilador

CC = g++
#CC = g++ -std=c++11
DX = doxygen
MK = make

#Bandera de depuracion

DEBUG = -g

#Banderas de compilacion

CFLAGS = -c -pg -Wall $(DEBUG) -pedantic
#CFLAGS = 

#Banderas para el Linker

LFLAGS = -Wall $(DEBUG) -pedantic

#Banderas para el ejecutable
EFLAGS = -Wall -pedantic -pg -g

#Reglas a ejecutar cuando se ejecute make

all:
	$(CC) $(CFLAGS) $(OBJS_CPP1)
	$(CC) $(CFLAGS) $(MAIN)
	$(CC) $(EFLAGS) -o $(TARGET) $(MAIN)
	$(DX) $(OBJS_DOC)
	$(MK) -C ./documentacion/latex/ all
	./ejecutable 16384 131072 > "./Resultados/Cache_16KB_128KB.txt"
	./ejecutable 16384 262144 > "./Resultados/Cache_16KB_256KB.txt"
	./ejecutable 32768 131072 > "./Resultados/Cache_32KB_128KB.txt"
	./ejecutable 32768 262144 > "./Resultados/Cache_32KB_256KB.txt"
	./ejecutable 65536 131072 > "./Resultados/Cache_64KB_128KB.txt"
	./ejecutable 65536 262144 > "./Resultados/Cache_64KB_256KB.txt"

$(MAIN) : $(OUT1)
	$(CC) $(EFLAGS) -o $(TARGET) $(MAIN)

$(OUT1) : $(HEADER1) $(OBJS_CPP1)
	$(CC) $(CFLAGS) $(OBJS_CPP1)

clean :
	-@rm -rf *.o documentacion/ 2>/dev/null || true
	clear

