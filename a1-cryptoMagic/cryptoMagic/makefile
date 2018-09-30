#  
#  FILE          : makeFile
#  PROJECT       : PROG1970 - System Programming - Assignment #1
#  PROGRAMMER    : Brendan Rushing
#  FIRST VERSION : 2018-05-20 
#  DESCRIPTION   : 
#	This make file will compile the source files found in the 
#	found in the ~/cryptoMagic directory.
#
# 
# =======================================================
#                  	cryptoMagic
# =======================================================
# FINAL BINARY Target
./bin/cryptoMagic : ./obj/source.o ./obj/encryptAndDecrypt.o
	cc ./obj/source.o ./obj/encryptAndDecrypt.o -o ./bin/cryptoMagic
#
# =======================================================
#                     Dependencies
# =======================================================                     
./obj/source.o : ./src/source.c ./inc/encryptAndDecrypt.h
	cc -c ./src/source.c -o ./obj/source.o

./obj/encryptAndDecrypt.o : ./src/encryptAndDecrypt.c ./inc/encryptAndDecrypt.h
	cc -c ./src/encryptAndDecrypt.c -o ./obj/encryptAndDecrypt.o

#
# =======================================================
# Other targets
# =======================================================                     
all : ./bin/cryptoMagic

clean:
	rm -f ./bin/*
	rm -f ./obj/*.o
	rm -f ./inc/*.h~
	rm -f ./src/*.c~



