
BIN = rgb_to_bw
CFLAGS = -Wall -Werror 
.PHONY: clean

all: $(BIN)

rgb_to_bw: rgb_to_bw.c
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm *.o rgb_to_bw
