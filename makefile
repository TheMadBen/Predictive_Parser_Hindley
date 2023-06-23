CC = g++
CFLAGS = -c -g -Wall -std=c++11

a.out: parser.o lexer.o inputbuf.o 
	g++ -o a.out parser.o lexer.o inputbuf.o

parser.o: parser.cc
	$(CC) $(CFLAGS) parser.cc

lexer.o: lexer.cc
	$(CC) $(CFLAGS) lexer.cc

inputbuf.o: inputbuf.cc
	$(CC) $(CFLAGS) inputbuf.cc

clean:
	rm *.o
