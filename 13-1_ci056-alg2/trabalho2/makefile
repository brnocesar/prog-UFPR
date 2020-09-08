######################## MAKEFILE ########################
all: moocars
moocars: moocars.o
	gcc moocars.o -o moocars
moocars.o: moocars.c
	gcc -c moocars.c -o moocars.o
clean:
	rm -rf *.o
