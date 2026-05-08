CC = gcc
CFLAGS = -g3
CLINK = -lm
BIN = main
INC = -I./inc
HEAD = $(shell find inc -type f -name "*.h")
SRC = $(shell find src -type f -name "*.c")
OBJ = $(SRC:src/%.c=obj/%.o)

.PHONY: all
all: $(BIN)

$(OBJ): obj/%.o : src/%.c $(HEAD)
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INC) -c -o $@ $< 

$(BIN): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

.PHONY: clean
clean:
	rm -f $(BIN)
	rm -rf obj
