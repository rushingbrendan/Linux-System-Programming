#  
#  FILE          : makeFile
#  PROJECT       : PROG1970 - System Programming - Assignment #4
#  PROGRAMMER    : Brendan Rushing
#  FIRST VERSION : 2018-08-01
#  DESCRIPTION   : 
#	This make file will compile the source files found in the 
#	found in the ~/server directory.
#
# 
# =======================================================
#                  	chat-server
# =======================================================



# FINAL BINARY Target
./bin/chat-server : ./obj/chat-server.o 
	cc ./obj/chat-server.o -o ./bin/chat-server -lpthread
#
# =======================================================
#                     Dependencies
# =======================================================                     
./obj/chat-server.o : ./src/chat-server.c ./inc/chat-server.h
	cc -c ./src/chat-server.c -o ./obj/chat-server.o


#
# =======================================================
# Other targets
# =======================================================                     
all : ./bin/server

clean:
	rm -f ./bin/*
	rm -f ./obj/*.o
	rm -f ./inc/*.h~
	rm -f ./src/*.c~


