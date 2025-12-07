all: virusdetector

virusdetector: virusdetector.o
	gcc -m32 -g -Wall -o virusdetector virusdetector.o

virusdetector.o: virusdetector.c
	gcc -m32 -g -Wall -c virusdetector.c -o virusdetector.o
	
clean:
	rm -f *.o  virusdetector 
