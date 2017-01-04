CC=gcc
CFLAGS=-Wall -Werror

main: main.o filereader.o elfheader.o
	$(CC) -o $@ $^

%.o: %.c                          
	$(CC) $(CFLAGS) -c $<

main.o : filereader.h elfheader.h elfsection.h
filereader.o: filereader.h
elfheader.o: elfheader.h filereader.h
elfsection.o: elfsection.h filereader.h
