#
# This makefile will compile all sources found in the
# current directory.
# =======================================================
#                  dataCorrupter
# =======================================================

CFLAGS=-Wall -Iinc
DEBUG=-g -O2

#
# =====================================================
#               Final binary Target
# =====================================================
./bin/dataCorrupter : ./obj/dataCorrupter.o ./obj/source.o ../common/obj/common.o
	cc ./obj/dataCorrupter.o ./obj/source.o ../common/obj/common.o -g -o ./bin/dataCorrupter

#
# =======================================================
#                  Dependencies
# =======================================================
./obj/dataCorrupter.o : ./src/dataCorrupter.c
	cc -c ./src/dataCorrupter.c $(CFLAGS) $(DEBUG) -o ./obj/dataCorrupter.o

./obj/source.o : ./src/source.c
	cc -c ./src/source.c $(CFLAGS) $(DEBUG) -o ./obj/source.o

#
# =======================================================
#                  Other targets
# =======================================================
all : ./bin/dataCorrupter

clean:
	rm -f ./bin/*
	rm -f ./obj/*.o
	rm -f ./inc/*.h~
	rm -f ./src/*.c~
	rm -f ./lib/*.a
	rm -f ./bin/*.so
