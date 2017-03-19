#
CFLAGS = -c -w -O3
LFLAGS = -lm -o

all: clean built run clean_b

built: getdat.o putdat.o evlib.o cmrlib.o main.o
	@gcc -fopenmp main.o getdat.o putdat.o evlib.o cmrlib.o $(LFLAGS) main.out

run:
	@time ./main.out

#---------------------------------------------#

getdat.o:
	@gcc $(CFLAGS) getdat.c

putdat.o:
	@gcc $(CFLAGS) putdat.c

evlib.o:
	@gcc $(CFLAGS) evlib.c

cmrlib.o:
	@gcc $(CFLAGS) cmrlib.c

main.o:
	@gcc $(CFLAGS) main.c

#---------------------------------------------#

clean:
	@rm -rf *.out *.o *.gch

clean_b:
	@rm -rf *.o *.gch
