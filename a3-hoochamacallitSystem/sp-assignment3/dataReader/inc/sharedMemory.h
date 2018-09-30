/*!
 *
 *	@file	:	sharedMemory.h
 *
 *	project	:	PROG1970 - Systems Programming - The Hoochamacallit System
 *
 *	@author	:	Brendan Rushing & Conor Macpherson
 *
 *	@date	:	2018-07-17
 *
 *	@brief	:	This fle contains data an function prototypes used for the function defined in
 *				../src/sharedMemory.c.
 *
 */


#ifndef SHAREDMEMORY_H
#define SHAREDMEMORY_H


#define SHMGET_ERROR -1
#define SHARED_MEMORY_DOES_NOT_EXIST -1
#define FTOK_ERROR -1
#define SHARED_MEMORY_ERROR -1


int getSharedMemoryID();


#endif /* SHAREDMEMORY_H */