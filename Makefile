CC = gcc

all: leArquivo
objects = #objetos

leArquivo: leArquivo.c 
	$(CC) leArquivo.c -o leArquivo 

clean:
	rm -f $(objects) 
	
purge: clean 
	rm -f #principal