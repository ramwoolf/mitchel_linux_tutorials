simple: simple.o
	gcc $(CFLAGS) -o bin/simple bin/simple.o

simple.o: simple.c
	gcc $(CFLAGS) -c simple.c
	mv simple.o bin/simple.o

getopt_long: getopt_long.o
	gcc $(CFLAGS) -o bin/getopt_long bin/getopt_long.o

getopt_long.o: getopt_long.c
	gcc $(CFLAGS) -c getopt_long.c
	mv getopt_long.o bin/getopt_long.o

clean:
	rm -f bin/*.o

cleanall:
	rm -rf bin/*