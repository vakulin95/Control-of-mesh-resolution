# Makefile

CFLAGS = -c -w -O3
LFLAGS = -lm -o

all: clean built run_base

one: clean built run_one

built: getdat.o putdat.o evlib.o cmrlib.o main.o
	@gcc $^ $(LFLAGS) main.out
	@make clean_b

run_one:
	@time ./main.out -o

run_base:
	@time ./main.out -b

#---------------------------------------------#
%.o: %.c
	@gcc $(CFLAGS) $< -o $@

#---------------------------------------------#

clean:
	@rm -rf *.out *.o *.gch

clean_b:
	@rm -rf *.o *.gch
