CC = gcc
CFLAGS = -std=c11 -Wall -Wextra
LDFLAGS = -lm

objects = leArquivo.o

all: fdtool

fdtool: fdtool.c leArquivo.o
	$(CC) fdtool.c -o fdtool leArquivo.o $(CFLAGS) $(LDFLAGS)

leArquivo.o: leArquivo.c 
	$(CC) -c leArquivo.c $(CFLAGS)

clean:
	rm -f $(objects) 
	
purge: clean 
	rm -f fdtool