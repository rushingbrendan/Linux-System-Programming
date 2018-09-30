#
# This makefile will compile all sources found in the
# current directory.
# =======================================================
#                  dataReader
# =======================================================

CFLAGS=-Wall -Iinc
DEBUG=-g -O2

#
# =====================================================
#               Final binary Target
# =====================================================
./bin/dataReader : ./obj/sharedMemory.o ./obj/messageQueue.o ./obj/dataReader.o
	cc ./obj/sharedMemory.o ./obj/messageQueue.o ./obj/dataReader.o ../common/obj/common.o -g -o ./bin/dataReader

#
# =======================================================
#                  Dependencies
# =======================================================
./obj/sharedMemory.o : ./src/sharedMemory.c
	cc -c ./src/sharedMemory.c $(CFLAGS) $(DEBUG) -o ./obj/sharedMemory.o

./obj/messageQueue.o : ./src/messageQueue.c
	cc -c ./src/messageQueue.c $(CFLAGS) $(DEBUG) -o ./obj/messageQueue.o

./obj/dataReader.o : ./src/dataReader.c
	cc -c ./src/dataReader.c $(CFLAGS) $(DEBUG) -o ./obj/dataReader.o

#
# =======================================================
#                  Other targets
# =======================================================
all : ./bin/dataReader

clean:
	rm -f ./bin/*
	rm -f ./obj/*.o
	rm -f ./inc/*.h~
	rm -f ./src/*.c~
	rm -f ./lib/*.a
	rm -f ./bin/*.so
