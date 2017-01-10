CC=gcc
CFLAGS=-Wall -Werror -g -std=c99

all: lecture fusion
lecture: main.o filereader.o elfheader.o elfsectiontab.o elfsection.o util.o elfsymbtab.o elfreloc.o fill_struct.o
	$(CC) -o $@ $^

fusion: testfus.o filereader.o elfheader.o elfsectiontab.o elfsection.o util.o elfsymbtab.o elfreloc.o fill_struct.o
	$(CC) -o $@ $^

%.o: %.c                          
	$(CC) $(CFLAGS) -c $<

main.o : filereader.h elfheader.h elfsectiontab.h elfsection.h elfsymbtab.h elfreloc.h fill_struct.h
filereader.o: filereader.h
elfheader.o: elfheader.h filereader.h
elfsectiontab.o : elfsectiontab.h filereader.h
elfsection.o : elfsection.h filereader.h
util.o : util.h
elfsymbtab.o: elfsymbtab.h elfsectiontab.h filereader.h
elfreloc.o: elfreloc.h elfsectiontab.h filereader.h util.h elfsection.h
sectionfus.o: elfheader.h elfsectiontab.h filereader.h sectionfus.h
fill_struct.o: filereader.h elfheader.h elfsectiontab.h elfsection.h elfsymbtab.h elfreloc.h
testfus.o : filereader.h elfheader.h elfsectiontab.h elfsection.h elfsymbtab.h elfreloc.h fill_struct.h

clean:
	rm main.o filereader.o elfheader.o elfsectiontab.o elfsection.o util.o elfsymbtab.o elfreloc.o fill_struct.o lecture
