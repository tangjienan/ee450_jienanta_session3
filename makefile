CC = gcc
CFLAGS = -I.



all: edge.o client.o server_and.o server_or.o
	


edge.o: edge.c
	gcc -o edge edge.c -I.
client.o: client.c
	gcc -o client client.c -I.
server_or.o: server_or.c
	gcc -o server_or server_or.c -I.
server_and.o: server_and.c
	gcc -o server_and server_and.c -I.
clean:
	rm -f *.o edge client server_and server_or

.PHONY:edge
.PHONY:server_and
.PHONY:server_or

edge: runedge
server_and:runand
server_or:runor

runedge: 
	./edge
runand:
	./server_and
runor:
	./server_or


