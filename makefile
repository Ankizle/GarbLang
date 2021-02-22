.PHONY: all
all: garblang.bin

.PHONY: clean
clean:
	rm -rf garblang.bin

.PHONY: test
test: all
	./garblang.bin test.garb
	g++ out.cc -o test.bin
	./test.bin

.PHONY: garblang.bin
garblang.bin:
	g++ -fpic -c parser/association.cc -o association.o
	g++ -fpic -c association.o parser/association_bind.cc -o association_bind.o
	g++ -fpic -c compiler/convert_statement.cc -o convert_statement.o
	gcc -c index.c -o garblang.o

	g++ -g association.o convert_statement.o association_bind.o garblang.o -o garblang.bin


