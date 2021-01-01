.PHONY: all
all: action.o garblang.bin

.PHONY: clean
clean:
	rm -rf garblang.bin action.o

.PHONY: garblang.bin
garblang.bin:
	gcc index.c -o garblang.bin action.o

action.o:
	g++ parser/actionizer.cc -c -o action.o