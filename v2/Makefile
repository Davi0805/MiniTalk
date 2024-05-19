CC = gcc
CFLAGS = -Wall -Wextra

all: client server

client: Client.c
	$(CC) $(CFLAGS) -o client Client.c

server: Server.c
	$(CC) $(CFLAGS) -o server Server.c

clean:
	rm -f client server
