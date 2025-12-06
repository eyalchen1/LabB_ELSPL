all: bubblesort hexaPrint virusdetector testfile

testfile: create_test_file.o
	gcc -m32 -g -Wall -o testfile create_test_file.o

virusdetector: virusdetector.o
	gcc -m32 -g -Wall -o virusdetector virusdetector.o

bubblesort: bubblesort.o
	gcc -m32 -g -Wall -o bubblesort bubblesort.o

hexaPrint: hexaPrint.o
	gcc -m32 -g -Wall -o hexaPrint hexaPrint.o

create_test_file.o: create_test_file.c
	gcc -m32 -g -Wall -c create_test_file.c -o create_test_file.o

bubblesort.o: bubblesort.c
	gcc -m32 -g -Wall -c bubblesort.c -o bubblesort.o

hexaPrint.o: hexaPrint.c
	gcc -m32 -g -Wall -c hexaPrint.c -o hexaPrint.o

virusdetector.o: virusdetector.c
	gcc -m32 -g -Wall -c virusdetector.c -o virusdetector.o
	

clean:
	rm -f *.o bubblesort hexaPrint virusdetector testfile
