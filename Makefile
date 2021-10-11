simple: simple.o
	gcc $(CFLAGS) -o bin/simple bin/simple.o

simple.o: simple.c
	gcc $(CFLAGS) -c simple.c
	mv simple.o bin/simple.o

clean:
	rm -f bin/*.o

cleanall:
	rm -rf bin/*