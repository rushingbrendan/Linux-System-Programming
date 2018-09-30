#
# This makefile will compile all sources found in the
# current directory.
# =======================================================
#                  dataCreator
# =======================================================

CFLAGS=-Wall -Iinc
DEBUG=-g -O2

#
# =====================================================
#               Final binary Target
# =====================================================
./bin/dataCreator : ./obj/dataCreator.o ./obj/source.o
	cc ./obj/dataCreator.o ./obj/source.o ../common/obj/common.o $(DEBUG) -o ./bin/dataCreator

#
# =======================================================
#                  Dependencies
# =======================================================
./obj/dataCreator.o : ./src/dataCreator.c
	cc -c ./src/dataCreator.c $(CFLAGS) $(DEBUG) -o ./obj/dataCreator.o

./obj/source.o : ./src/source.c
	cc -c ./src/source.c $(CFLAGS) $(DEBUG) -o ./obj/source.o

#
# =======================================================
#                  Other targets
# =======================================================
all : ./bin/dataCreator

clean:
	rm -f ./bin/*
	rm -f ./obj/*.o
	rm -f ./inc/*.h~
	rm -f ./src/*.c~
