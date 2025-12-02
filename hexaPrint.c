
#include <stdio.h>
int main(int argc, char **argv){
    unsigned char* buffer= malloc(2048);
    FILE* file = fopen(argv[1], "rb");
    if(file!=NULL){
        fread(buffer, 1, 2048, file);
        printHex(buffer,13);
        }

}

void printHex(unsigned char* buffer, int length){
    for(int i=0; i<length; i++){
        printf("%x ", buffer[i]);
    }
}