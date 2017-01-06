CC=gcc
CFLAGS=-Wall -Werror -g -std=c99

main: main.o filereader.o elfheader.o elfsectiontab.o elfsection.o util.o elfsymbtab.o elfreloc.o
	$(CC) -o $@ $^

%.o: %.c                          
	$(CC) $(CFLAGS) -c $<

main.o : filereader.h elfheader.h elfsectiontab.h elfsection.h elfsymbtab.h elfreloc.h
filereader.o: filereader.h
elfheader.o: elfheader.h filereader.h
elfsectiontab.o : elfsectiontab.h filereader.h
elfsection.o : elfsection.h filereader.h
util.o : util.h
elfsymbtab.o: elfsymbtab.h elfsectiontab.h filereader.h
elfreloc.o: elfreloc.h elfsectiontab.h filereader.h util.h
clean:
	rm main.o filereader.o elfheader.o elfsectiontab.o elfsection.o util.o elfsymbtab.o elfreloc.o
