IDIR =./include
CC=gcc
CXX=g++
FLAGS= COMMONFLAGS = -rtl -O0

ODIR=./obj
LDIR=./lib
SDIR=./src
LIBS=

ifdef DEBUG
    COMMONFLAGS := $(COMMONFLAGS) -g
endif

BINFILE1 = messagerA
BINFILE2 = messagerB
BINFILE3 = dummy

all: A B C

A: $(BINFILE1)
B: $(BINFILE2)
C: $(BINFILE3)

_DEPS = message.h 
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ1 = messagerA.o 
OBJ1 = $(patsubst %,$(ODIR)/%,$(_OBJ1))

_OBJ2 = messagerB.o
OBJ2 = $(patsubst %,$(ODIR)/%,$(_OBJ2))

_OBJ3 = dummy.o
OBJ3 = $(patsubst %,$(ODIR)/%,$(_OBJ3))

    
$(ODIR)/%.o : $(SDIR)/%.c $(DEPS)
	$(CC) $(CFLAGS) -c $< -o $@ 

$(BINFILE1): $(OBJ1) 
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

$(BINFILE2): $(OBJ2) 
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

$(BINFILE3): $(OBJ3) 
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean all

clean:
	rm -f $(ODIR)/*.o *~ $(BINFILE1) $(BINFILE2) $(BINFILE3) 
