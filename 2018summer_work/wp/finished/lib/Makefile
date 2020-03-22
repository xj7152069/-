INCLUDE = ../include

liballoc.a: alloc.o
	ar rs liballoc.a alloc.o

alloc.o: alloc.c
	cc -c alloc.c -I$(INCLUDE)

clean:
	rm -f *.o
