#  
#  FILE          : makeFile
#  PROJECT       : PROG1970 - System Programming - Assignment #2
#  PROGRAMMER    : Brendan Rushing
#  FIRST VERSION : 2018-05-20 
#  DESCRIPTION   : 
#	This make file will compile the source files found in the 
#	found in the ~/encodeInput directory.
#
# 
# =======================================================
#                  	encodeInput
# =======================================================
# FINAL BINARY Target
./bin/encodeInput : ./obj/source.o ./obj/asm.o ./obj/srec.o
	cc ./obj/source.o ./obj/srec.o ./obj/asm.o -o ./bin/encodeInput
#
# =======================================================
#                     Dependencies
# =======================================================                     
./obj/source.o : ./src/source.c ./inc/asm.h ./inc/srec.h
	cc -c ./src/source.c -o ./obj/source.o

./obj/srec.o : ./src/srec.c ./inc/srec.h
	cc -c ./src/srec.c -o ./obj/srec.o

./obj/asm.o : ./src/asm.c ./inc/asm.h
	cc -c ./src/asm.c -o ./obj/asm.o

#
# =======================================================
# Other targets
# =======================================================                     
all : ./bin/encodeInput

clean:
	rm -f ./bin/*
	rm -f ./obj/*.o
	rm -f ./inc/*.h~
	rm -f ./src/*.c~



