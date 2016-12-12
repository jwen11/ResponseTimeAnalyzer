IDIR =./include
CC=gcc
CXX=g++
FLAGS= COMMONFLAGS = -Wall -Wextra -pedantic

ODIR=./obj
LDIR=./lib
SDIR=./src
LIBS=

MKDIR_P = mkdir -p

ifdef DEBUG
    COMMONFLAGS := $(COMMONFLAGS) -g
endif



BINFILE = analyser

_DEPS = task.h file_handler.h analysis.h message.h config.h misc.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = task.o file_handler.o analysis.o main.o message.o misc.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

all: dirs $(BINFILE) 
    
$(ODIR)/%.o : $(SDIR)/%.cpp $(DEPS)
	$(CXX) $(CFLAGS) -c $< -o $@ 

$(BINFILE): $(OBJ) 
	$(CXX) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean all dirs

clean:
	rm -rf $(ODIR) *~ $(BINFILE) 

dirs: ${ODIR} 
${ODIR}:
	${MKDIR_P} ${ODIR}
