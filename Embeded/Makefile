all: embedded-sql

%.c: %.ec
	ecpg $<
	
%.o: %.c
	gcc -g -O0 -Wall -Werror -c -I/usr/include/postgresql $<
	
embedded-sql: embedded-sql.o main.o
	gcc -o $@ $^ -lecpg
	
clean:
	rm -rf *.o embedded-sql *~ embedded-sql.c