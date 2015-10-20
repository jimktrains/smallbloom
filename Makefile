CFLAGS = -g --std=c99 -Os

fnv.o: fnv.h fnv.c
	cc ${CFLAGS} -c $^

libsmallbloom.o: libsmallbloom.c libsmallbloom.h fnv.h
	cc ${CFLAGS} -c $^

test:  libsmallbloom.o fnv.o smallbloom.c test_dids.h
	cc ${CFLAGS} -o smallbloom $^
	./smallbloom
clean:
	rm -f smallbloom *.o
