all:
	gcc -c diff.c error.c parse.c simplify.c struct.c utility.c
	gcc diff.o error.o parse.o simplify.o struct.o utility.o main.c -o main

clean:
	rm *.o
	rm derivative
