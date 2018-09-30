#
# This makefile will compile all sources listed for all.
# =======================================================


all :
	+$(MAKE) -C common
	+$(MAKE) -C dataCreator
	+$(MAKE) -C dataReader
	+$(MAKE) -C dataCorrupter

	rm -rf ./program

	mkdir program
	mkdir program/bin

	cp dataCreator/bin/dataCreator program/bin
	cp dataCorrupter/bin/dataCorrupter program/bin
	cp dataReader/bin/dataReader program/bin/

clean:
	rm -rf */bin/*
	rm -rf */obj/*.o
	rm -rf */inc/*.h~
	rm -rf */src/*.c~
	rm -rf */lib/*.a
	rm -rf */bin/*.so
	rm -rf ./program
