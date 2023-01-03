.PHONY:clean all
CC=cc
CFLAGS=-Wall -g
BIN=01_byteorder 02addr
all:$(BIN)
%.o:%.c
	$(CC) $(CFLAGS) -c $< -o $@
clean:
	rm -f *.o $(BIN)
