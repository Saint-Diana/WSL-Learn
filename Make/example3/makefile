main : main.o max.o
	gcc main.o max.o -o main

main.o : main.c
	gcc -c main.c -o main.o

max.o : max.c
	gcc -c max.c -o max.o

clean :
	rm main main.o max.o