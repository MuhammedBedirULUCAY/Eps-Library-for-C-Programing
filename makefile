
output:1901042697.o library.o
	gcc 1901042697.o library.o -o output -lm

1901042697.o: 1901042697.c
	gcc -c -lm 1901042697.c

library.o: library.c
	gcc -c -lm library.c

clean:
	rm *.o outout

