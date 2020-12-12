.PHONY: all
all: garblang.bin

.PHONY: clean
clean:
	rm -rf garblang.bin

.PHONY: garblang.bin
garblang.bin:
	gcc index.c -o garblang.bin