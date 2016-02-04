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

all: A B

A: $(BINFILE1)
B: $(BINFILE2)

_DEPS = message.h 
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ1 = messagerA.o 
OBJ1 = $(patsubst %,$(ODIR)/%,$(_OBJ1))

_OBJ2 = messagerB.o
OBJ2 = $(patsubst %,$(ODIR)/%,$(_OBJ2))

    
$(ODIR)/%.o : $(SDIR)/%.c $(DEPS)
	$(CC) $(CFLAGS) -c $< -o $@ 

$(BINFILE1): $(OBJ1) 
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

$(BINFILE2): $(OBJ2) 
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean all

clean:
	rm -f $(ODIR)/*.o *~ $(BINFILE1) $(BINFILE2) 
