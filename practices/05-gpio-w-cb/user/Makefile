PROJECT=boleta
CFLAGS=-Wall -std=c11
LFLAGS=-lpthread -lm
CC=arm-linux-gnueabihf-gcc

all: $(PROJECT)

%.o: %.c
	$(CC) -c $< $(CFLAGS)

$(PROJECT): $(patsubst %.c,%.o,$(wildcard *.c))
	$(CC) $^ -o $@ $(LFLAGS)

.PHONY: clean

clean:
	rm -f *.o $(PROJECT)