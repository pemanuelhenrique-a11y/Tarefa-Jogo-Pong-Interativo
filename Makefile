# Makefile

# Linka códigos-objeto (cria executável bibtela)
default: bibtela.c libbibtela.a
	gcc -I/usr/include t04_pong.c -o pong -L. -l bibtela -l ncursesw -lm

# Compila bibtela.c (cria código-objeto bibtela.o)
libbibtela.a: bibtela.o
	ar rc libbibtela.a bibtela.o

# Compila bibtela.c (cria código-objeto bibtela.o)
bibtela.o: bibtela.c bibtela.h
	gcc -I/usr/include -c bibtela.c -o bibtela.o 

# Remove executável e códigos-objeto
clean:
	rm -f crand *.o *.a *.pdf
