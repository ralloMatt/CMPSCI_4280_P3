CC=gcc 
CFLAGS=-c

all: testSem

testSem: main.o parser.o treePrint.o scanner.o 
	$(CC) -o testSem main.o parser.o treePrint.o scanner.o 

main.o: main.c
	$(CC) $(CFLAGS) main.c

parser.o: parser.c parser.h
	$(CC) $(CFLAGS) parser.c

treePrint.o: treePrint.c treePrint.h
	$(CC) $(CFLAGS) treePrint.c

scanner.o: scanner.c scanner.h 
	$(CC) $(CFLAGS) scanner.c

clean:
	rm *.o testSem
