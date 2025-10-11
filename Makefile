CC = gcc
CFLAGS = -std=c11 -Wall -Wextra
LDFLAGS = -lm

objects = #objetos

all: leArquivo

leArquivo: leArquivo.c 
	$(CC) leArquivo.c $(CFLAGS) -o leArquivo 


clean:
	rm -f $(objects) 
	
purge: clean 
	rm -f leArquivo #Trocar para main no futuro