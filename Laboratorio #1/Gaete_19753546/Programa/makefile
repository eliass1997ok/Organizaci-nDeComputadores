CABECERA1 = ./structs.h
CABECERA2 = ./functions.h

all: ./functions.c $(CABECERA1) $(CABECERA2)
	gcc -o main.o ./main.c ./functions.c -Wall

clean:
	-rm -f main.o
run: 
	./main.o