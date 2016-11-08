CC = clang
LDFLAGS = -lm
CFLAGS = -std=c99 -Wall -Wextra -g

all: koch
	@# ./koch 50 270 4 0xFF0000 0xFFFFFF koch.ppm all
	@# ./koch 50 270 1 0xFF0000 0xFFFFFF koch.ppm all
	@# valgrind ./koch 50 270 4 0xFF0000 0xFFFFFF koch.ppm all
	valgrind ./koch 150 4 0xFF0000 0xFFFFFF fract.ppm all

koch: koch_main.o koch_fonctions.o koch_ihm.o create_image.o
	$(CC) $(LDFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f *.o *~ koch *.ppm
