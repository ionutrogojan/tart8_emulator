default: main.c
	gcc main.c -lraylib -lm -o main
	./main