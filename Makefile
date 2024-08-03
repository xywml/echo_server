CC=gcc
CFLAGS=-Iinclude

all: echo_server

echo_server: main.o server.o utils.o log_utils.o
	$(CC) -o echo_server main.o server.o utils.o log_utils.o

main.o: src/main.c
	$(CC) -c src/main.c $(CFLAGS)

server.o: src/server.c include/server.h
	$(CC) -c src/server.c $(CFLAGS)

utils.o: src/utils.c include/utils.h
	$(CC) -c src/utils.c $(CFLAGS)

log_utils.o: src/log_utils.c include/log_utils.h
	$(CC) -c src/log_utils.c $(CFLAGS)

clean:
	rm -f *.o echo_server

