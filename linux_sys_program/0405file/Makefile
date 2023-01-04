.PHONY:clean all
CC=cc
CFLAGS=-Wall -g
BIN=01errno 02fd 03fd 04open 05cp 06lseek 07hole 08ls
all:$(BIN)
%.o:%.c
	$(CC) $(CFLAGS) -c $< -o $@
clean:
	rm -f *.o $(BIN)
