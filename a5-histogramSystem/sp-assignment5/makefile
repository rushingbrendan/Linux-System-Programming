#
# This makefile will compile all sources listed for all.
# =======================================================


all :
	+$(MAKE) -C common
	+$(MAKE) -C dataConsumer
	+$(MAKE) -C dataProducer1
	+$(MAKE) -C dataProducer2

	rm -rf ./program

	mkdir program
	mkdir program/bin

	cp dataConsumer/bin/dataConsumer program/bin
	cp dataProducer1/bin/dataProducer1 program/bin
	cp dataProducer2/bin/dataProducer2 program/bin/

clean:
	rm -rf */bin/*
	rm -rf */obj/*.o
	rm -rf */inc/*.h~
	rm -rf */src/*.c~
	rm -rf */lib/*.a
	rm -rf */bin/*.so
	rm -rf ./program
