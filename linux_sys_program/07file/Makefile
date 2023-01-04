.PHONY:clean all
CC=cc
CFLAGS=-Wall -g
BIN= 01fileshare 02dup
all:$(BIN)
%.o:%.c
	$(CC) $(CFLAGS) -c $< -o $@
clean:
	rm -f *.o $(BIN)
