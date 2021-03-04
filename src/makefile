.PHONY: all
all: garblang.bin

.PHONY: clean
clean:
	rm -rf association_bind.o
	rm -rf association.o
	rm -rf convert_statement.o
	rm -rf garblang.o
	rm -rf garblang.bin
	rm -rf benchmarks/garblang.bin
	rm -rf github.com

.PHONY: garblang.bin
garblang.bin:
	g++ -fpic -c parser/association.cc -o association.o
	g++ -fpic -c association.o parser/association_bind.cc -o association_bind.o
	g++ -fpic -c compiler/convert_statement.cc -o convert_statement.o
	gcc -c index.c -o garblang.o

	g++ -g association.o convert_statement.o association_bind.o garblang.o -o garblang.bin

.PHONY: compare
benchmark: all
	rm -rf benchmarks/data.xlsx

	mv garblang.bin benchmarks/garblang.bin
	GOPATH=$(CURDIR)/../ go get github.com/360EntSecGroup-Skylar/excelize
	cd benchmarks && GOPATH=$(CURDIR)/../ go run start.go
