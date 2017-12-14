#static linking - link randcpuid.o and randmain.o -> randmain executable 
#link C libraries before executing main 
#link randmain with -ldl -Wl,-rpath=$PWD
#compiles libhw and libsw w/ FPIC
#build shared object files hw.so and sw.so with -shared
#use strace to debug
CC = gcc
CFLAGS = $(OPTIMIZE) -g3 -Wall -Wextra -march=native -mtune=native -mrdrnd
 
randcpuid.o: randcpuid.c
	$(CC) $(CFLAGS) -fPIC -c randcpuid.c -o randcpuid.o

randmain.o: randmain.c
	$(CC) $(CFLAGS) -fPIC -c randmain.c -o randmain.o

randlibhw.o: randlibhw.c
	 $(CC) $(CFLAGS) -fPIC -c randlibhw.c -o randlibhw.o

randlibsw.o: randlibsw.c
	 $(CC) $(CFLAGS) -fPIC -c randlibsw.c -o randlibsw.o
randlibhw.so: randlibhw.o
	 $(CC) -shared -o randlibhw.so randlibhw.o
randlibsw.so: randlibsw.o
	$(CC) -shared -o randlibsw.so randlibsw.o
randmain: randmain.o randcpuid.o
	$(CC) $(CFLAGS) -ldl -Wl,-rpath=$(PWD) randmain.o randcpuid.o -o randmain















