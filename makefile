.PHONY: all
all: garblang.bin

.PHONY: clean
clean:
	rm -rf garblang.bin

.PHONY: garblang.bin
garblang.bin:
	g++ -fpic -c parser/association.cc -o association.o
	g++ -fpic -c association.o parser/association_bind.cc -o association_bind.o
	gcc -c index.c -o garblang.o
	g++ -g association.o association_bind.o garblang.o -o garblang.bin


