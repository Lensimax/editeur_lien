CC=gcc
CFLAGS=-Wall -Werror

main: filereader.o elfheader.o
	$(CC) -o $@ $^

%.o: %.c                          
	$(CC) $(CFLAGS) -c $<

filereader.o: filereader.h
elfheader.o: elfheader.h filereader.h
