IDIR =./include
CC=gcc
CXX=g++
FLAGS= COMMONFLAGS = -Wall -Wextra -pedantic

ODIR=./obj
LDIR=./lib
SDIR=./src
LIBS=

ifdef DEBUG
    COMMONFLAGS := $(COMMONFLAGS) -g
endif

BINFILE = analyse

_DEPS = task.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = task.o main.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

all:$(BINFILE)
    
$(ODIR)/%.o : $(SDIR)/%.cpp $(DEPS)
	$(CXX) $(CFLAGS) -c $< -o $@ 

$(BINFILE): $(OBJ) 
	$(CXX) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean all

clean:
	rm -f $(ODIR)/*.o *~ $(BINFILE) 
