#
# This makefile will compile all sources found in the
# current directory.
# =======================================================
#                  dataProducer1
# =======================================================

CFLAGS=-Wall -Iinc
DEBUG=-g -O2

#
# =====================================================
#               Final binary Target
# =====================================================
./bin/dataProducer1 : ./obj/dataProducer1.o ./obj/source.o ../common/obj/common.o
	cc ./obj/dataProducer1.o ./obj/source.o ../common/obj/common.o -g -o ./bin/dataProducer1

#
# =======================================================
#                  Dependencies
# =======================================================
./obj/dataProducer1.o : ./src/dataProducer1.c 
	cc -c ./src/dataProducer1.c $(CFLAGS) $(DEBUG) -o ./obj/dataProducer1.o

./obj/source.o : ./src/source.c	../common/inc/semaphoreStruct.h
	cc -c ./src/source.c $(CFLAGS) $(DEBUG) -o ./obj/source.o

#
# =======================================================
#                  Other targets
# =======================================================
all : ./bin/dataProducer1

clean:
	rm -f ./bin/*
	rm -f ./obj/*.o
	rm -f ./inc/*.h~
	rm -f ./src/*.c~
	rm -f ./lib/*.a
	rm -f ./bin/*.so
