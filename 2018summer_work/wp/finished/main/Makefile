INCLUDE = ../include
LIB = ../lib

CFLAGS = -O3

OBJECTS = modeling.o
EXECS = modeling.exe

$(EXECS): $(OBJECTS)
	g++ -o $(EXECS) $(OBJECTS) -L$(LIB) -lpar -lsu -lcwp -lalloc $(CFLAGS) 

$(OBJECTS): modeling.cpp
	g++ -c modeling.cpp -I$(INCLUDE) $(CFLAGS)

clean:
	rm -f *.o *.exe; pwd

