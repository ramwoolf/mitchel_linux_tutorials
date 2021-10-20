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

thread_create: thread_create.o
	gcc $(CFLAGS) -o bin/thread_create bin/thread_create.o -lpthread

thread_create.o: thread_create.c
	gcc $(CFLAGS) -c thread_create.c
	mv thread_create.o bin/thread_create.o

bad_get_primes: bad_get_primes.o
	gcc $(CFLAGS) -o bin/bad_get_primes bin/bad_get_primes.o -lpthread

bad_get_primes.o: bad_get_primes.c
	gcc $(CFLAGS) -c bad_get_primes.c
	mv bad_get_primes.o bin/bad_get_primes.o

thread_journal: thread_journal.o
	gcc $(CFLAGS) -o bin/thread_journal bin/thread_journal.o -lpthread

thread_journal.o: thread_journal.c
	gcc $(CFLAGS) -fno-stack-protector -c thread_journal.c
	mv thread_journal.o bin/thread_journal.o

producers_consumers: producers_consumers.o
	gcc $(CFLAGS) -o bin/producers_consumers bin/producers_consumers.o -lpthread

producers_consumers.o: producers_consumers.c
	gcc $(CFLAGS) -c producers_consumers.c
	mv producers_consumers.o bin/producers_consumers.o

clean:
	rm -f bin/*.o
	rm -f bin/*.log

cleanall:
	rm -rf bin/*