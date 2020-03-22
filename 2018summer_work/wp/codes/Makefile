RSFHOME=/usr/local/cwp
BIN=./

INCLUDE=$(RSFHOME)/include
LIB=$(RSFHOME)/lib

CFLAGS= -c

FFLAGS= -lm -lpar -lcwp -lsu -lpar

MODULE=abc

EXECS=$(BIN)/$(MODULE).exe

OBJECTS=$(MODULE).o

.c.o: 
	cc $(CFLAGS) -I$(INCLUDE) $<

$(EXECS): $(OBJECTS)
	cc -L$(LIB)  $(OBJECTS) -o $@ $(FFLAGS)

clean:
	rm -f *.o
