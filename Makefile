all:
	gcc -o main *.c ed/*.c -I. -lm -lpthread
