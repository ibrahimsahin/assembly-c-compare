all: 	perfcompc.o perfcompa.o
	gcc -m32 -o perfcomp perfcompc.o perfcompa.o
perfcompc.o:
	gcc -m32 -c perfcomp.c -o perfcompc.o
perfcompa.o:
	nasm -f elf perfcomp.asm -o perfcompa.o
clean:
	rm *.o
