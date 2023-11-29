# Eric Kivel - GRR20220069 | Murilo Paes - GRR20190158
TARGET = ajustePol

SRCDIR = ./src ./src/*
INCDIR = ./include
LOGSDIR = ./logs
RESULTDIR = ./resultados

CC 			  = gcc
CFILES 		= $(foreach D, $(SRCDIR), $(wildcard $(D)/*.c))
LIKFLAGS   = -I${LIKWID_INCLUDE} -DLIKWID_PERFMON
CFLAGS		= -O3 -mavx -march=native 
LDFLAGS		= -lm -I$(INCDIR) -L${LIKWID_LIB} -llikwid
OBJFILES 	= $(patsubst %.c, %.o, $(CFILES))

all: $(TARGET)

$(TARGET): $(OBJFILES)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS) 

%.o: %.c
	$(CC) $(CFLAGS) $(LIKFLAGS) $(LDFLAGS) -c -o $@ $^

clean:
	rm -f $(OBJFILES)

purge: clean
	rm -f $(TARGET) *.txt 

.PHONY: all clean purge
