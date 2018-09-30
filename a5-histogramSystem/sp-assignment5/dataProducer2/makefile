#
# This makefile will compile all sources found in the
# current directory.
# =======================================================
#                  dataProducer2
# =======================================================

CFLAGS=-Wall -Iinc
DEBUG=-g -O2

#
# =====================================================
#               Final binary Target
# =====================================================
./bin/dataProducer2 : ./obj/dataProducer2.o ./obj/source.o
	cc ./obj/dataProducer2.o ./obj/source.o ../common/obj/common.o $(DEBUG) -o ./bin/dataProducer2

#
# =======================================================
#                  Dependencies
# =======================================================
./obj/dataProducer2.o : ./src/dataProducer2.c
	cc -c ./src/dataProducer2.c $(CFLAGS) $(DEBUG) -o ./obj/dataProducer2.o

./obj/source.o : ./src/source.c	../common/inc/semaphoreStruct.h ../dataConsumer/inc/sharedMemory.h
	cc -c ./src/source.c $(CFLAGS) $(DEBUG) -o ./obj/source.o

#
# =======================================================
#                  Other targets
# =======================================================
all : ./bin/dataProducer2

clean:
	rm -f ./bin/*
	rm -f ./obj/*.o
	rm -f ./inc/*.h~
	rm -f ./src/*.c~
