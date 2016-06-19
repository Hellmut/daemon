#g++ main.cpp config.cpp outlet.cpp daemonizer.cpp -o test_daemon -I./include -pthread -DDEBUG

IDIR =./include
CC=g++
CFLAGS=-I$(IDIR)

ODIR=./obj
LDIR =./lib

LIBS=-pthread

PFLAGS= -DDEBUG

_DEPS = config.hpp outlet.hpp daemonizer.hpp 
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = main.o config.o outlet.o daemonizer.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))


$(ODIR)/%.o: src/%.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS) $(PFLAGS)

test_daemon: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ 
