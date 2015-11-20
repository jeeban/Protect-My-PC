c: main.c
	clear
	gcc main.c -o main -Wall -Wextra `pkg-config --libs --cflags gtk+-2.0`
r:c
	clear
	./main
	
