.PHONY:clean all
CC=cc
CFLAGS=-Wall -g
BIN= 01stat
all:$(BIN)
%.o:%.c
	$(CC) $(CFLAGS) -c $< -o $@
clean:
	rm -f *.o $(BIN)
