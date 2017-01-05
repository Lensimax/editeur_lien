CC=gcc
CFLAGS=-Wall -Werror -g

main: main.o filereader.o elfheader.o elfsectiontab.o elfsection.o util.o
	$(CC) -o $@ $^

%.o: %.c                          
	$(CC) $(CFLAGS) -c $<

main.o : filereader.h elfheader.h elfsectiontab.h elfsection.h
filereader.o: filereader.h
elfheader.o: elfheader.h filereader.h
elfsectiontab.o : elfsectiontab.h filereader.h
elfsection.o : elfsection.h filereader.h
util.o : util.h
clean:
	rm elfsectiontab.o elfheader.o filereader.o main.o
