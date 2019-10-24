CC=gcc
CFLAGS=-Wall -ansi -pedantic -I.
OBJ=a3.o common.o binary.o name.o title.o principals.o
HEADER_ALL=common.h binary.h name.h title.h principals.h
HEADER=common.h binary.h

a3: $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $@

a3.o: main.c $(HEADER_ALL)
	$(CC) $(CFLAGS) -c main.c -o $@

common.o: common.c common.h
	$(CC) $(CFLAGS) -c $< -o $@

binary.o: binary.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

name.o: name.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

title.o: title.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

principals.o: principals.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm a3 *.o
