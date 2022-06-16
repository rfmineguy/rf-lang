all: clean main

main: main.o
	ld -o main main.o

main.o: main.asm
	yasm -f elf64 -m amd64 -g dwarf2 main.asm -l main.lst 

clean:
	rm -f ./main.o
	rm -f ./main.lst
	rm -f ./main
