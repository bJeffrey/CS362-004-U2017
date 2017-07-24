CFLAGS=-Wall

default: testme

testme: testme.o
	gcc -o testme testme.o
	testme

testme.o: testme.c
	gcc -c testme.c

clean:
	rm testme *.o
