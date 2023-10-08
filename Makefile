# Eric Kivel - GRR20220069 | Murilo Paes - GRR20190158
TARGET = ajustePol

SRCDIR = ./src ./src/*
INCDIR = ./include

CC 			= gcc
CFILES 		= $(foreach D, $(SRCDIR), $(wildcard $(D)/*.c))
# CFLAGS 		= -O3 -mavx -march=native
CFLAGS		= -O3 -mavx -march=native -I${LIKWID_INCLUDE} -DLIKWID_PERFMON
# LDFLAGS 	= -lm $(foreach D, $(INCDIR), -I$(D))
LDFLAGS		= -lm -I$(INCDIR) -L${LIKWID_LIB} -llikwid
OBJFILES 	= $(patsubst %.c, %.o, $(CFILES))

all: $(TARGET)

$(TARGET): $(OBJFILES)
	$(CC) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) $(LDFLAGS) -c -o $@ $^

clean:
	rm -f $(TARGET) $(OBJFILES)

purge: 
	rm -f $(TARGET) $(OBJFILES) *.txt *.log
