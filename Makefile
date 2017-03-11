CFLAGS = -c #-Wall
LFLAGS = -lm -o

all: clean built run

built: getdat.o putdat.o main.o
	@gcc main.o getdat.o putdat.o $(LFLAGS) main.out

run:
	@./main.out

#---------------------------------------------#

getdat.o:
	@gcc $(CFLAGS) getdat.c

putdat.o:
	@gcc $(CFLAGS) putdat.c

main.o:
	@gcc $(CFLAGS) main.c

#---------------------------------------------#

clean:
	@rm -rf *.out *.o *.gch
