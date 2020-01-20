CC=gcc
CFLAGS=-Wall -ansi -pedantic -Iinclude

BIN=bin/
INC=include/
SRC=src/

OBJ=$(BIN)main.o $(BIN)common.o $(BIN)binary.o $(BIN)name.o $(BIN)title.o $(BIN)principals.o
HEADER_ALL=$(INC)common.h $(INC)binary.h $(INC)name.h $(INC)title.h $(INC)principals.h
HEADER=$(INC)common.h $(INC)binary.h

main: $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(BIN)$@

$(BIN)main.o: $(SRC)main.c $(HEADER_ALL)
	$(CC) $(CFLAGS) -c $(SRC)main.c -o $@

$(BIN)common.o: $(SRC)common.c $(INC)common.h
	$(CC) $(CFLAGS) -c $< -o $@

$(BIN)binary.o: $(SRC)binary.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

$(BIN)name.o: $(SRC)name.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

$(BIN)title.o: $(SRC)title.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

$(BIN)principals.o: $(SRC)principals.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm $(BIN)*
