#
# Makefile for the chat-client portion of Assignment 4 for PROG1970
# The "Can We Talk?" System
#
# Author: Josh Rogers
# Date: August 2, 2018
#
# =======================================================
#                  Assignment5
# =======================================================

BIN_DIR = ./bin
OBJ_DIR = ./obj
SRC_DIR = ./src
INC_DIR = ./inc

TARGET = ${BIN_DIR}/chat-client
OBJS = ${OBJ_DIR}/client.o ${OBJ_DIR}/messageHandler.o ${OBJ_DIR}/stringHandler.o 

CC = cc
CC_FLAGS = -I${INC_DIR}

# FINAL BINARY Target
${TARGET} : ${OBJS}
	${CC} ${OBJS} -o $@ -lncurses -pthread

#
# =======================================================
#                     Dependencies
# =======================================================
${OBJS}: ${OBJ_DIR}/%.o: ${SRC_DIR}/%.c
	${CC} -c ${CC_FLAGS} $< -o $@

#
# =======================================================
# Other targets
# =======================================================
.PHONY : clean all

all : ${TARGET}

clean:
	rm -f ${BIN_DIR}/*
	rm -f ${OBJ_DIR}/*.o
	rm -f ${INC_DIR}/*.h~
	rm -f ${SRC_DIR}/*.c~




