CFLAGS = -g --std=c99
*.o: *.c
	cc ${CFLAGS} -c $^

test: smallbloom.o
	cc ${CFLAGS} -o smallbloom $^
	./smallbloom
clean:
	rm -f smallbloom *.o
