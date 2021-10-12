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

run_child_proc: run_child_proc.o
	gcc $(CFLAGS) -o bin/run_child_proc bin/run_child_proc.o

run_child_proc.o: run_child_proc.c
	gcc $(CFLAGS) -c run_child_proc.c
	mv run_child_proc.o bin/run_child_proc.o

run_child_proc_nonblock: run_child_proc_nonblock.o
	gcc $(CFLAGS) -o bin/run_child_proc_nonblock bin/run_child_proc_nonblock.o

run_child_proc_nonblock.o: run_child_proc_nonblock.c
	gcc $(CFLAGS) -c run_child_proc_nonblock.c
	mv run_child_proc_nonblock.o bin/run_child_proc_nonblock.o

clean:
	rm -f bin/*.o

cleanall:
	rm -rf bin/*