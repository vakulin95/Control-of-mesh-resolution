CFLAGS = -c #-Wall
LFLAGS = -lm -o

all: clean built run clean_b

built: getdat.o putdat.o evlib.o main.o
	@gcc main.o getdat.o putdat.o evlib.o $(LFLAGS) main.out

run:
	@./main.out

#---------------------------------------------#

getdat.o:
	@gcc $(CFLAGS) getdat.c

putdat.o:
	@gcc $(CFLAGS) putdat.c

evlib.o:
	@gcc $(CFLAGS) evlib.c

main.o:
	@gcc $(CFLAGS) main.c

#---------------------------------------------#

clean:
	@rm -rf *.out *.o *.gch

clean_b:
	@rm -rf *.o *.gch
