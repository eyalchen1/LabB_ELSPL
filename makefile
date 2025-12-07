all: AntiVirus

virusdetector: AntiVirus.o
	gcc -m32 -g -Wall -o AntiVirus AntiVirus.o

virusdetector.o: AntiVirus.c
	gcc -m32 -g -Wall -c AntiVirus.c -o AntiVirus.o
	
clean:
	rm -f *.o  AntiVirus 
