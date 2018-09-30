#
# This makefile will compile all sources found in the
# current directory.
# =======================================================
#                  dataConsumer
# =======================================================

CFLAGS=-Wall -Iinc
DEBUG=-g -O2

#
# =====================================================
#               Final binary Target
# =====================================================
./bin/dataConsumer : ./obj/sharedMemory.o  ./obj/dataConsumer.o
	cc ./obj/sharedMemory.o  ./obj/dataConsumer.o ../common/obj/common.o -g -o ./bin/dataConsumer

#
# =======================================================
#                  Dependencies
# =======================================================
./obj/sharedMemory.o : ./src/sharedMemory.c
	cc -c ./src/sharedMemory.c $(CFLAGS) $(DEBUG) -o ./obj/sharedMemory.o


./obj/dataConsumer.o : ./src/dataConsumer.c	../common/inc/semaphoreStruct.h
	cc -c ./src/dataConsumer.c $(CFLAGS) $(DEBUG) -o ./obj/dataConsumer.o

#
# =======================================================
#                  Other targets
# =======================================================
all : ./bin/dataConsumer

clean:
	rm -f ./bin/*
	rm -f ./obj/*.o
	rm -f ./inc/*.h~
	rm -f ./src/*.c~
	rm -f ./lib/*.a
	rm -f ./bin/*.so
