TARGET = ajustePol

SRCDIR = ./src ./src/curveFit
INCDIR = ./include

CC 			= gcc
CFILES 		= $(foreach D, $(SRCDIR), $(wildcard $(D)/*.c))
CFLAGS 		= -O3 -mavx -march=native
LDFLAGS 	= $(foreach D, $(INCDIR), -I$(D))
LBFLAGS 	= -lm
OBJFILES 	= $(patsubst %.c, %.o, $(CFILES))

all: $(TARGET)

$(TARGET): $(OBJFILES)
	$(CC) -o $@ $^ $(LBFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) $(LDFLAGS) -c -o $@ $^

clean:
	rm -f $(TARGET) $(OBJFILES)

