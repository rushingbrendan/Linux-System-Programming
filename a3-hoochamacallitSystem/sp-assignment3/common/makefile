#
# This makefile will compile all sources found in the
# current directory.
# =======================================================
#                  common
# =======================================================

CFLAGS=-Wall -Iinc
DEBUG=-g -O2

#
# =======================================================
#                  Dependencies
# =======================================================
./obj/common.o : ./src/common.c
	cc -c ./src/common.c $(CFLAGS) $(DEBUG) -o ./obj/common.o

#
# =======================================================
#                  Other targets
# =======================================================

clean:
	rm -f ./bin/*
	rm -f ./obj/*.o
	rm -f ./inc/*.h~
	rm -f ./src/*.c~
	rm -f ./lib/*.a
	rm -f ./lib/*.so
