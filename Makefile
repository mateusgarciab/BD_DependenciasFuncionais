CC = gcc
CFLAGS = -std=c11 -Wall -Wextra
LDFLAGS = -lm

objects = leArquivo.o operacoes.o buscaLargura.o

all: fdtool

fdtool: fdtool.c $(objects)
	$(CC) fdtool.c -o fdtool $(objects) $(CFLAGS) $(LDFLAGS)

leArquivo.o: leArquivo.c 
	$(CC) -c leArquivo.c $(CFLAGS)

operacoes.o: operacoes.c 
	$(CC) -c operacoes.c $(CFLAGS)

buscaLargura.o: buscaLargura.c 
	$(CC) -c buscaLargura.c $(CFLAGS)

clean:
	rm -f $(objects) 
	
purge: clean 
	rm -f fdtool